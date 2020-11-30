#include "Scenes/SceneHeatingSettings.h"
#include "App.h"

// *** Public Methods Overriding ***
void	SceneHeatingSettings::Initialize()
{
	Serial.printf("<== scene SceneHeatingSettings ==>\n");
	Scene::Initialize();

	// regle de trois pour passer à 0-100%, 100% étant la valeur max réelle maximum définie dans App.h
	m_current_percentage = DataSaveLoad::ReadCurrentHeatingPercentage() * 100 / MAX_PERCENTAGE_HEATER;

	// clear screen
	app->Graphics.Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw title
	app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
	app->Graphics.Screen.drawString(TextContent::text_settings_chauffage, 80, 8);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_chauffage_puissance_FR, 80, 28);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_validate_FR, 80, 100);
	
	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_RED, SPIRULERIE_LIGHT);
}

void	SceneHeatingSettings::Destroy()
{
	Scene::Destroy();
}

void	SceneHeatingSettings::Update()
{
	if (m_current_percentage > 100)
		m_current_percentage = 0;
	else if (m_current_percentage < 0)
		m_current_percentage = 100;

	Scene::Update();
}

void	SceneHeatingSettings::Draw(GraphicsEngine *graphics)
{
	// fill
	graphics->Screen.fillRect(0, 50, 160, 30, SPIRULERIE_LIGHT);

	graphics->Screen.setCursor(54, 54);
	graphics->Screen.printf("%d %%", m_current_percentage);

	graphics->DrawLeftArrow();
	graphics->DrawRightArrow();

	Scene::Draw(graphics); // push sprite to screen
}

void	SceneHeatingSettings::OnButtonClic(BTN btn)
{
	// autre regle de trois pour passer du pourcentage choisi au pourcentage réel en prenant en compte la limite max définie dans App.h
	uint8_t	real_percentage = m_current_percentage * MAX_PERCENTAGE_HEATER / 100;

	switch (btn)
	{
	case BTN::LEFT:
		m_current_percentage -= 1;
		break;
	case BTN::MIDDLE:
		DataSaveLoad::SetCurrentHeatingPercentage(real_percentage);
		app->LoadScene(new SceneMainMenu());
		break;
	case BTN::RIGHT:
		m_current_percentage += 1;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}


// PRIVATE
