#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "Scenes/Scene.h"

class	TestScene : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;
};

#endif