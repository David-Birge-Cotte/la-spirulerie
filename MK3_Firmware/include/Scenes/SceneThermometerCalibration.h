#ifndef SCENE_THERMOMETER_CALIBRATION_H
#define SCENE_THERMOMETER_CALIBRATION_H

#include "Scenes/Scene.h"
#include "DataSaveLoad.h"

class	SceneThermometerCalibration : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	float	adjustement;
};

#endif