#ifndef SCENE_TIME_H
#define SCENE_TIME_H

#include "Scenes/Scene.h"

class	SceneTime : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	int8_t	m_time;
};

#endif