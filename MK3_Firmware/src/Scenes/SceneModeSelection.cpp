#include "Scenes/SceneModeSelection.h"
#include "App.h"

// *** SOME C ENUMS (to cast as uint8_t) ***
enum	MODE { HIBERNATION, NORMAL, CUSTOM };

void SceneModeSelection::Initialize()
{
	Serial.printf("<== scene SceneModeSelection ==>\n");
	Scene::Initialize();

	// get current mode stored in hardware
	m_selection = DataSaveLoad::ReadCurrentMode();

	// Prepare fonts now before Draw()
	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);

}

void SceneModeSelection::Update()
{
	Scene::Update();

	// check boundaries
	if (m_selection > 2)
		m_selection = 2;
	else if (m_selection < 0)
		m_selection = 0;

	// choose the right text to show according to selection
	switch (m_selection)
	{
	case HIBERNATION:
		m_selection_text = TextContent::text_mode_hibernation_FR;
		break;
	case NORMAL:
		m_selection_text = TextContent::text_mode_normal_FR;
		break;
	case CUSTOM:
		m_selection_text = TextContent::text_mode_custom_FR;
		break;
	default:
		break;
	}
}

void SceneModeSelection::Draw(GraphicsEngine *graphics)
{
	graphics->DrawScreen(SPIRULERIE_LIGHT);

	app->Graphics.Screen.textcolor = SPIRULERIE_BLUE;
	app->Graphics.Screen.drawString(TextContent::text_menu_mode_FR, 80, 10);

	app->Graphics.Screen.textcolor = SPIRULERIE_GREEN;
	app->Graphics.Screen.drawString(m_selection_text, 80, 28);

	app->Graphics.Screen.textcolor = SPIRULERIE_RED;
	app->Graphics.Screen.drawString(TextContent::text_select_FR, 80, 100);

	switch (m_selection)
	{
	case HIBERNATION:
		graphics->Screen.fillRoundRect(16, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	case NORMAL:
		graphics->Screen.fillRoundRect(64, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	case CUSTOM:
		graphics->Screen.fillRoundRect(112, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	default:
		break;
	}

	graphics->Screen.drawRoundRect(16, 56, 32, 32, 4, SPIRULERIE_GREEN);
	graphics->Screen.drawRoundRect(64, 56, 32, 32, 4, SPIRULERIE_GREEN);
	graphics->Screen.drawRoundRect(112, 56, 32, 32, 4, SPIRULERIE_GREEN);

	graphics->DrawImage(Sprites::hibernation_32_32, 16, 56, 32, 32);
	graphics->DrawImage(Sprites::light_max_32x32, 64, 56, 32, 32);
	graphics->DrawImage(Sprites::plus_sign, 112, 56, 32, 32);

	Scene::Draw(graphics); // push sprite to screen
}

void SceneModeSelection::OnButtonClic(BTN btn)
{
	Scene::OnButtonClic(btn);
	
	switch (btn)
	{
	case BTN::LEFT:
		if (m_progress == 0)
			m_selection--;
		break;
	case BTN::MIDDLE:
		m_progress++;
		DataSaveLoad::SetCurrentMode(m_selection); // save selected mode
		if (m_selection != CUSTOM)
		{
			app->modeNeedsRefresh = true;
			app->LoadScene(new SceneMainMenu());
		}
		else
			app->LoadScene(new SceneCustomModeSettings());
		break;
	case BTN::RIGHT:
		if (m_progress == 0)
			m_selection++;
		break;
	default:
		break;
	}
}

void SceneModeSelection::Destroy()
{
	Scene::Destroy();
}

// *** PRIVATE METHODS ***