#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H

#include "Scenes/Scene.h"

class	SceneMainMenu : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	void	DrawDayNightCycle(uint8_t hour, uint8_t dawn, uint8_t dusk);
	void	DrawTemperature(uint16_t x, uint16_t y, float temperature);
};

#endif