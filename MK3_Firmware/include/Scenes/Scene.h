#ifndef SCENE_H
#define SCENE_H

#include "DataTypes.h"
#include "GraphicsEngine/GraphicsEngine.h"

// forward declaration. Need including App.h in each scene .c files
class	Application;

// Base class for inherited screens.
// Screens are small scenes with graphics and button logic
class	Scene
{
	public:
	virtual void Initialize();
	virtual void Update();
	virtual void Destroy();

	virtual void Draw(GraphicsEngine *graphics);
	virtual void OnButtonClic(BTN btn);

	protected:
	Application		*app;	// storing a reference to the Application;
};

#endif