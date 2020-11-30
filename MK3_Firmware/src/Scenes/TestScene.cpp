#include "Scenes/TestScene.h"
#include "GraphicsEngine/Vector2.h"
#include "GraphicsEngine/SimplexNoise.h"
#include "App.h"

Vector2 pos;

void TestScene::Initialize()
{
	Serial.printf("<== scene TestScene ==>\n");
	Scene::Initialize();
}

void TestScene::Update()
{
	float noisyX = (SimplexNoise::noise(millis() / 1500.0f) * 40);
	float noisyY = (SimplexNoise::noise(millis() / 1500.0f + 50) * 40);

	pos.X = (WIN_WIDTH / 2) + noisyX - 8;
	pos.Y = (WIN_HEIGHT / 2) + noisyY - 8;
	
	Scene::Update();
}

void TestScene::Draw(GraphicsEngine *graphics)
{
	graphics->DrawScreen(SPIRULERIE_LIGHT);
	//graphics->Screen.fillRoundRect(pos.X, pos.Y, 16, 16, 8, SPIRULERIE_GREEN);

	float current_millis = millis() / 2000.0f;
	int x = 5;
	float scale = 0.01f;
	while (x < WIN_WIDTH)
	{
		float noiseY = 
			SimplexNoise::noise(current_millis + x * scale) * 30 + (WIN_HEIGHT / 2);

		graphics->Screen.drawCircle(x, noiseY, 4, SPIRULERIE_GREEN);
		x += 10;
	}

	static int y = 0;
	y--;
	//graphics->DrawImage(pixel_noir, 0, y, 450, 510);

	Scene::Draw(graphics);
}

void TestScene::OnButtonClic(BTN btn)
{
	Application::singleton->LoadScene(new SceneMainMenu());
	Scene::OnButtonClic(btn);
}

void TestScene::Destroy()
{
	Scene::Destroy();
}