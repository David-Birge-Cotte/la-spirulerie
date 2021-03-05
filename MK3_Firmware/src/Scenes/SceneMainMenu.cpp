#include "Scenes/SceneMainMenu.h"
#include "App.h"

// *** PUBLIC INHERITED METHODS ***

void SceneMainMenu::Initialize()
{
	Serial.printf("<== scene Main Menu ==>\n");
	Scene::Initialize();

	app->isOnMainMenu = true;
	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_LIGHT, SPIRULERIE_GREEN/*SPIRULERIE_GREY*/);
	app->PlayMelody(Melodies::VALID);
}

void SceneMainMenu::Update()
{

	Scene::Update();
}

void SceneMainMenu::Draw(GraphicsEngine *graphics)
{
	// clear screen
	graphics->DrawScreen(SPIRULERIE_GREY);

	// draw sky and sun / stars
	DrawDayNightCycle(hour(), app->parameters.hour_dawn, app->parameters.hour_dusk);
	// draw green bottom half
	graphics->Screen.fillRect(0, 64, 160, 64, SPIRULERIE_GREEN);
	// show the current temperature
	DrawTemperature(24, 80, app->GetCurrentTemperature());

	//if (app->heatNominal)
	//	graphics->DrawImage(Sprites::chauffage_32_32, 18, 80, 32, 32); // trop moche

	// draw possible moves out of the screen
	graphics->DrawRightArrow();

	Scene::Draw(graphics);
}

void SceneMainMenu::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		//app->LoadScene(new TestScene());
		break;
	case BTN::MIDDLE:
		break;
	case BTN::RIGHT:
		app->isOnMainMenu = false;
		app->LoadScene(new SceneTopMenu());
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}

void SceneMainMenu::Destroy()
{
	Scene::Destroy();
}

void	SceneMainMenu::DrawDayNightCycle(uint8_t hour, uint8_t dawn, uint8_t dusk)
{
	// check if night
	if (hour < dawn || hour >= dusk)
	{
		// draw the night sky
		app->Graphics.Screen.fillRect(0, 0, 160, 64, SPIRULERIE_GREY);
		for (int i = 0; i < 32; i++)
		{
			float x = SimplexNoise::noise((float)i / 0.37f);
			float y = SimplexNoise::noise((float)i / 0.83f);

			// remap noise from [-1;1] to [0;screen_size]
			x = (x + 1) / 2.0f * 160.0f;
			y = (y + 1) / 2.0f * 64.0f;

			// draw a star
			app->Graphics.Screen.drawPixel(x, y, SPIRULERIE_LIGHT);
		}
		return;
	}

	// draw blue sky
	app->Graphics.Screen.fillRect(0, 0, 160, 64, SPIRULERIE_BLUE);

	uint8_t	num_day_hours = dusk - dawn;
	uint8_t	current_day_hour = hour - dawn;
	uint8_t	percentage_of_day = (uint8_t)((float)current_day_hour / (float)num_day_hours * 100.0f);

	uint8_t	r = 48;
	float	t = (float)map(percentage_of_day, 0, 100, 180, 360) * DEG_TO_RAD;

	uint8_t	sun_x = r*cos(t) + 80;
	uint8_t	sun_y = r*sin(t) + 64 + 16;

	app->Graphics.DrawImage(Sprites::sun_40x40, sun_x - 20, sun_y - 20, 40, 40);
}

void	SceneMainMenu::DrawTemperature(uint16_t x, uint16_t y, float temperature)
{
	app->Graphics.DrawImage(Sprites::thermometer_32x32, x, y, 32, 32);

	app->Graphics.Screen.setCursor(x + 26, y + 6);
	if (temperature - DataSaveLoad::ReadThermometerAdjustement() != -1)
		app->Graphics.Screen.printf("%.1f°C", temperature);
	else
		app->Graphics.Screen.printf(". . . . °C");
}