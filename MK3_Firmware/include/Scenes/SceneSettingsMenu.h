#ifndef SCENE_SETTINGS_MENU_H
#define SCENE_SETTINGS_MENU_H

#include "Scenes/Scene.h"

class	SceneSettingsMenu : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	int8_t	m_selection = 0;
	String	m_menu_name;

	void	ValidateSelection();
};

#endif