#ifndef HARVEST_H
#define HARVEST_H

#include "Scenes/Scene.h"

class	Harvest : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	uint8_t	m_progress = 0;
	uint8_t	m_speed = 5;

	void PumpHarvest();

	void DrawPreparation();
	void DrawHarvest();
	void DrawStop();
};

#endif