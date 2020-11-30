#ifndef SCENE_SCREENSAVER_SETTINGS_H
#define SCENE_SCREENSAVER_SETTINGS_H

#include "Scenes/Scene.h"
#include "DataSaveLoad.h"

class	SceneScreenSaverSettings : public Scene
{
	public:
	void Initialize() override;
	void Update() override;
	void Draw(GraphicsEngine *graphics) override;
	void OnButtonClic(BTN btn) override;
	void Destroy() override;

	private:
	bool	m_current_selection;
};

#endif