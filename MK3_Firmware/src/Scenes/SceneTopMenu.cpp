#include "Scenes/SceneTopMenu.h"
#include "App.h"

enum MENU { PUMP, MODE, SETTINGS, GAMES };

// *** PUBLIC INHERITED METHODS ***

void SceneTopMenu::Initialize()
{
	Serial.printf("<== scene Top Menu ==>\n");
	Scene::Initialize();

	app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_RED, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(MC_DATUM);
}

void SceneTopMenu::Update()
{
	if (m_selection < 0 || m_selection > 2) // 3 with games
	{
		app->LoadScene(new SceneMainMenu());
		return;
	}

	if (m_selection == MENU::PUMP)
		m_menu_name = TextContent::text_menu_pump_FR;
	if (m_selection == MENU::MODE)
		m_menu_name = TextContent::text_menu_mode_FR;
	if (m_selection == MENU::SETTINGS)
		m_menu_name = TextContent::text_menu_settings_FR;
	if (m_selection == MENU::GAMES)
		m_menu_name = TextContent::text_menu_games_FR;
	
	m_menu_name = "[" + m_menu_name + "]";

	Scene::Update();
}


void SceneTopMenu::Draw(GraphicsEngine *graphics)
{
	graphics->Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw possible moves out of screen
	graphics->DrawLeftArrow();
	graphics->DrawRightArrow();

	// print selected menu name
	graphics->Screen.drawString(m_menu_name, 80, 64);

	Scene::Draw(graphics); // push sprite to screen
}

void SceneTopMenu::OnButtonClic(BTN btn)
{
	Scene::OnButtonClic(btn);
	
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
}

void SceneTopMenu::Destroy()
{
	Scene::Destroy();
}

// *** PRIVATE METHODS ***

void SceneTopMenu::ValidateSelection()
{
	switch (m_selection)
	{
	case MENU::PUMP:
		app->LoadScene(new ScenePumpUse());
		break;
	case MENU::MODE:
		app->LoadScene(new SceneModeSelection());
		break;
	case MENU::SETTINGS:
		app->LoadScene(new SceneSettingsMenu());
		break;
	case MENU::GAMES:
		break;
	default:
		break;
	}
}