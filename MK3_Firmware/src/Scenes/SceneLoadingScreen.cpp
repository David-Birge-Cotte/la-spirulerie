#include "Scenes/SceneLoadingScreen.h"
#include "App.h"

void SceneLoadingScreen::Initialize()
{
	Serial.printf("<== scene Loading Screen ==>\n");
	Scene::Initialize();

	start_millis = millis();

	// The booting jingle is a required cultural element !
	app->PlayMelody(Melodies::BOOT);

	app->Graphics.LoadFont("Comfortaa_22", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
}

void SceneLoadingScreen::Update()
{
	if (millis() - start_millis > BOOT_TIME)
	{
		// Exit the loading screen to load the Main Menu
		Application::singleton->LoadScene(new SceneMainMenu());
		return;
	}

	Scene::Update();
}

void SceneLoadingScreen::Draw(GraphicsEngine *graphics)
{
	graphics->Screen.fillSprite(SPIRULERIE_LIGHT);
	graphics->Screen.drawString(TextContent::text_title, 80, 16);

	int32_t percentage = (millis() - start_millis) * 100 / BOOT_TIME;
	float current_millis = millis() / 300.0f;
	int x = 20;
	float scale = 0.05f;
	int circle_size = 4;

	if (percentage > 95)	circle_size = 1;
	else if (percentage > 90)	circle_size = 2;
	else if (percentage > 80)	circle_size = 3;

	while (x <= WIN_WIDTH - 20)
	{
		float noiseY =
			SimplexNoise::noise(current_millis + x * scale) * 20.0f + 80;

		graphics->Screen.drawCircle(x, noiseY, circle_size, SPIRULERIE_GREEN);
		x += 10;
	}

	Scene::Draw(graphics);
}

void SceneLoadingScreen::OnButtonClic(BTN btn)
{
	// The user should not be able to do anything when it is a loading screen
}

void SceneLoadingScreen::Destroy()
{
	Scene::Destroy();
}