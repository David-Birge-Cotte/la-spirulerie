#ifndef SCENE_HEATING_SETTINGS_H
#define SCENE_HEATING_SETTINGS_H

#include "Scenes/Scene.h"
#include "DataSaveLoad.h"

class	SceneHeatingSettings : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	int8_t	m_current_percentage;
};

#endif