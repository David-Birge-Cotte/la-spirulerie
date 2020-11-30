#ifndef SCENE_TOP_MENU_H
#define SCENE_TOP_MENU_H

#include "Scenes/Scene.h"

class	SceneTopMenu : public Scene
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