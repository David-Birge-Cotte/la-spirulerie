#ifndef SCENE_CUSTOM_MODE_SETTINGS
#define SCENE_CUSTOM_MODE_SETTINGS

#include "Scenes/Scene.h"

class	SceneCustomModeSettings : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	void	Validate();

	int8_t		m_selection;
	uint8_t		m_progress = 0;
	String		m_title_text;
	String		m_helper_text;
	String		m_selection_text;
	ModeParameters	m_custom_mode;
};


#endif