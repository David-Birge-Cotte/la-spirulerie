#include "Scenes/SceneThermometerCalibration.h"
#include "App.h"

// *** Public Methods Overriding ***

void	SceneThermometerCalibration::Initialize()
{
	Serial.printf("<== scene SceneThermometerCalibration ==>\n");
	Scene::Initialize();

	adjustement = DataSaveLoad::ReadThermometerAdjustement(); // read current value

	// clear screen
	app->Graphics.Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw title
	app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
	app->Graphics.Screen.drawString(TextContent::text_menu_therm_FR, 80, 8);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_therm_calibration_FR, 80, 28);

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_RED, SPIRULERIE_LIGHT);
	app->Graphics.Screen.drawString(TextContent::text_validate_FR, 80, 100);
	
	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_RED, SPIRULERIE_LIGHT);
}

void	SceneThermometerCalibration::Destroy()
{
	Scene::Destroy();
}

void	SceneThermometerCalibration::Update()
{
	if (adjustement > 2)
		adjustement = 2;
	else if (adjustement < -2)
		adjustement = -2;
	else if (adjustement < 0.1f && adjustement > -0.1f)
		adjustement = 0;

	Scene::Update();
}

void	SceneThermometerCalibration::Draw(GraphicsEngine *graphics)
{
	// fill 
	graphics->Screen.fillRect(0, 50, 160, 30, SPIRULERIE_LIGHT);

	graphics->Screen.setCursor(64, 54);
	graphics->Screen.printf("%.1f", adjustement);

	graphics->DrawLeftArrow();
	graphics->DrawRightArrow();

	Scene::Draw(graphics); // push sprite to screen
}

void	SceneThermometerCalibration::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		adjustement -= 0.1f;
		break;
	case BTN::MIDDLE:
		DataSaveLoad::SetThermometerAdjustement(adjustement);
		app->LoadScene(new SceneMainMenu());
		break;
	case BTN::RIGHT:
		adjustement += 0.1f;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}


// PRIVATE
