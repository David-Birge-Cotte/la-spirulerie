#include "Scenes/SceneScreenSaverSettings.h"
#include "App.h"

// *** Public Methods Overriding ***
void	SceneScreenSaverSettings::Initialize()
{
	Serial.printf("<== scene SceneScreenSaverSettings ==>\n");
	Scene::Initialize();

	// récupération du parametre actuellement sauvegardé
	m_current_selection = DataSaveLoad::ReadCanScreenSave();

	// clear screen
	app->Graphics.Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw title
	app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
	app->Graphics.Screen.drawString(TextContent::text_settings_veille, 80, 8);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_veille_actif_FR, 80, 28);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_validate_FR, 80, 100);
	
	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_RED, SPIRULERIE_LIGHT);
}

void	SceneScreenSaverSettings::Destroy()
{
	Scene::Destroy();
}

void	SceneScreenSaverSettings::Update()
{
	Scene::Update();
}

void	SceneScreenSaverSettings::Draw(GraphicsEngine *graphics)
{
	// fill
	graphics->Screen.fillRect(0, 50, 160, 30, SPIRULERIE_LIGHT);

	graphics->Screen.setCursor(54, 54);
	if (m_current_selection == true)
	{
		graphics->Screen.printf(TextContent::text_oui_FR);
		graphics->DrawLeftArrow();
	}
	else
	{
		graphics->Screen.printf(TextContent::text_non_FR);
		graphics->DrawRightArrow();
	}

	Scene::Draw(graphics); // push sprite to screen
}

void	SceneScreenSaverSettings::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		m_current_selection = false;
		break;
	case BTN::MIDDLE:
		// sauvegarde du nouveau parametre
		DataSaveLoad::SetCanScreenSave(m_current_selection);
		app->LoadScene(new SceneMainMenu());
		break;
	case BTN::RIGHT:
		m_current_selection = true;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}


// PRIVATE
