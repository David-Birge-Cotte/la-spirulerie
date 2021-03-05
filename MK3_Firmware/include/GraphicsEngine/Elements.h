#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "Vector2.h"
#include "GraphicsEngine.h"

/* 
** Elements have properties and behaviours
** they are instantiable / destructibles dynamically in scenes
** equivalent of game objects in game engines
*/

/*
** Base class to inherit
*/
class Element
{
	public:
		Vector2 Position;
		
		virtual void	Initialize();
		virtual void	Update();
		virtual void	Draw(GraphicsEngine *graphics);
};

class PopUp : public Element
{
	public:
		void	Initialize() override;
		void	Update() override;
		void	Draw(GraphicsEngine *graphics) override;

		void	Show(bool animate);
		void	Hide();
		bool	IsShowned();

		String	Line1;
		String	Line2;
		String	Line3;
		String	Line4;

	private:
		uint16_t	percentage;
		uint64_t	t_start;
		bool		is_animating = false;
		uint16_t	anim_speed_ms = 300;
		bool		show = false;
};


#endif