#ifndef PURGE_H
#define PURGE_H

#include "Scenes/Scene.h"

class	Purge : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	uint8_t	m_progress = 0;

	void PumpHarvest();

	void DrawPreparation();
	void DrawPurge();
	void DrawStop();
};

#endif