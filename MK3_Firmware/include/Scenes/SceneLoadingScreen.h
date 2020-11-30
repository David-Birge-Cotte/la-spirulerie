#ifndef SCENE_LOADING_SCREEN_H
#define SCENE_LOADING_SCREEN_H

#include "Scenes/Scene.h"

#define BOOT_TIME 3300

class	SceneLoadingScreen : public Scene
{
	public:
		void Initialize() override;
		void Update() override;
		void Draw(GraphicsEngine *graphics) override;
		void OnButtonClic(BTN btn) override;
		void Destroy() override;

	private:
		unsigned long start_millis = 0;
};

#endif