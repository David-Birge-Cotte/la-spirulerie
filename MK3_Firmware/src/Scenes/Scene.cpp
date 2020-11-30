#include "Scenes/Scene.h"
#include "App.h"

void Scene::Initialize()
{
	// storing a reference to the main Application
	app = Application::singleton;
}

void Scene::Update()
{

}

void Scene::Draw(GraphicsEngine *graphics)
{
	graphics->PushToScreen();
}

void Scene::OnButtonClic(BTN btn)
{
	// Seems to makes the PWM driving the LEDs flash/stop for a few ms ?
	//Application::singleton->PlayMelody(Melodies::VALID);
}

void Scene::Destroy()
{
	//app->Graphics.Screen.unloadFont();
}