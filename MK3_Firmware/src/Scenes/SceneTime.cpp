#include "Scenes/SceneTime.h"
#include "App.h"

// *** Public Methods Overriding ***

void	SceneTime::Initialize()
{
	Serial.printf("<== scene SceneTime ==>\n");
	Scene::Initialize();

	m_time = hour();

	app->Graphics.Screen.fillSprite(SPIRULERIE_LIGHT);

	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
	app->Graphics.Screen.drawString(TextContent::text_menu_time_FR, 80, 16);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_validate_FR, 80, 100);

	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_RED, SPIRULERIE_LIGHT);
}

void	SceneTime::Destroy()
{
	Scene::Destroy();
}

void	SceneTime::Update()
{
	if (m_time > 23)
		m_time = 0;
	else if (m_time < 0)
		m_time = 23;

	Scene::Update();
}

void	SceneTime::Draw(GraphicsEngine *graphics)
{
	graphics->Screen.fillRect(0, 50, 160, 30, SPIRULERIE_LIGHT);

	graphics->Screen.textcolor = SPIRULERIE_RED;
	graphics->Screen.setCursor(68, 54);
	graphics->Screen.printf("%d", m_time);

	graphics->DrawLeftArrow();
	graphics->DrawRightArrow();

	Scene::Draw(graphics); // push sprite to screen
}

void	SceneTime::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		m_time--;
		break;
	case BTN::MIDDLE:
		TimeSystem::SetTime(m_time, 0);
		app->LoadScene(new SceneMainMenu());
		break;
	case BTN::RIGHT:
		m_time++;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}