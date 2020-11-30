#ifndef SCENE_PUMP_USE_H
#define SCENE_PUMP_USE_H

#include "Scenes/Scene.h"

class	ScenePumpUse : public Scene
{
	public:
	void	Initialize() override;
	void	Update() override;
	void	Draw(GraphicsEngine *graphics) override;
	void	OnButtonClic(BTN btn) override;
	void	Destroy() override;

	private:
	uint8_t	m_progress;
	uint8_t	m_pump_mode;
};

#endif