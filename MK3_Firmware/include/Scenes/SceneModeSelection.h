#ifndef SCENE_MODE_SELECTION_H
#define SCENE_MODE_SELECTION_H

#include "Scenes/Scene.h"

class	SceneModeSelection : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	int8_t	m_selection;
	uint8_t	m_progress = 0;
	String	m_selection_text;
};

#endif