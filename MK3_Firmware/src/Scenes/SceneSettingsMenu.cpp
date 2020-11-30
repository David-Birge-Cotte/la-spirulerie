#include "Scenes/SceneSettingsMenu.h"
#include "App.h"

// *** Public Methods Overriding ***

void	SceneSettingsMenu::Initialize()
{
	Serial.printf("<== scene SceneSettingsMenu ==>\n");
	Scene::Initialize();
}

void	SceneSettingsMenu::Destroy()
{
	Scene::Destroy();
}

void	SceneSettingsMenu::Update()
{
	// check boundaries
	if (m_selection < 0)
		m_selection = 0;
	else if (m_selection > 3)
		m_selection = 3;

	switch (m_selection)
	{
	case 0:
		app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_RED, SPIRULERIE_LIGHT);
		app->Graphics.Screen.setTextDatum(MC_DATUM);
		m_menu_name = TextContent::text_settings_heure_FR;
		break;
	case 1:
		app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
		app->Graphics.Screen.setTextDatum(MC_DATUM);
		m_menu_name = TextContent::text_settings_therm_FR;
		break;
	case 2:
		app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
		app->Graphics.Screen.setTextDatum(MC_DATUM);
		m_menu_name = TextContent::text_settings_chauffage;
		break;
	case 3:
		app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_RED, SPIRULERIE_LIGHT);
		app->Graphics.Screen.setTextDatum(MC_DATUM);
		m_menu_name = TextContent::text_settings_veille;
	}

	m_menu_name = "[" + m_menu_name + "]";

	Scene::Update();
}

void	SceneSettingsMenu::Draw(GraphicsEngine *graphics)
{
	// clear screen
	graphics->Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw possible moves
	if (m_selection == 0)
		graphics->DrawRightArrow();
	else if (m_selection == 3)
		graphics->DrawLeftArrow();
	else
	{
		graphics->DrawLeftArrow();
		graphics->DrawRightArrow();
	}

	// print selected menu name
	graphics->Screen.drawString(m_menu_name, 80, 64);

	// push sprite to screen
	Scene::Draw(graphics);
}

void	SceneSettingsMenu::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		m_selection--;
		break;
	case BTN::MIDDLE:
		ValidateSelection();
		break;
	case BTN::RIGHT:
		m_selection++;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}


// PRIVATE
void	SceneSettingsMenu::ValidateSelection()
{
	if (m_selection == 0)
		Application::singleton->LoadScene(new SceneTime());
	else if (m_selection == 1)
		Application::singleton->LoadScene(new SceneThermometerCalibration());
	else if (m_selection == 2)
		Application::singleton->LoadScene(new SceneHeatingSettings());
	else if (m_selection == 3)
		Application::singleton->LoadScene(new SceneScreenSaverSettings());
}