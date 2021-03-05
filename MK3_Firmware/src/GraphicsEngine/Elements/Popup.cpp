#include "GraphicsEngine/Elements.h"

void	PopUp::Initialize()
{

}

void	PopUp::Update()
{
	if (!show)
		return;

	uint16_t milli_count = millis() - t_start;
	if (milli_count >= anim_speed_ms)
		is_animating = false;

	percentage = ((float)milli_count / (float)anim_speed_ms) * 100;
}

void	PopUp::Draw(GraphicsEngine *graphics)
{
	if (!show)
		return;

	if (is_animating)
	{
		uint16_t val = 100 - percentage;
		graphics->Screen.fillRoundRect(12 + val / 4, 12 + val / 4, WIN_WIDTH - 24 - val / 2, WIN_HEIGHT - 24 - val / 2, 8, SPIRULERIE_LIGHT);
		graphics->Screen.drawRoundRect(12 + val / 4, 12 + val / 4, WIN_WIDTH - 24 - val / 2, WIN_HEIGHT - 24 - val / 2, 8, SPIRULERIE_BLUE);
		return;
	}

	graphics->Screen.fillRoundRect(12, 12, WIN_WIDTH - 24, WIN_HEIGHT - 24, 8, SPIRULERIE_LIGHT);
	graphics->Screen.drawRoundRect(12, 12, WIN_WIDTH - 24, WIN_HEIGHT - 24, 8, SPIRULERIE_BLUE);
	graphics->Screen.drawRoundRect(13, 13, WIN_WIDTH - 26, WIN_HEIGHT - 26, 6, SPIRULERIE_BLUE);

	graphics->Screen.drawString(Line1, WIN_WIDTH / 2, WIN_HEIGHT / 2 - 42);
	graphics->Screen.drawString(Line2, WIN_WIDTH / 2, WIN_HEIGHT / 2 - 20);
	graphics->Screen.drawString(Line3, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 2);
	graphics->Screen.drawString(Line4, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 24);
}

void	PopUp::Show(bool animate)
{
	show = true;
	is_animating = animate;
	t_start =  millis();
}

void	PopUp::Hide()
{
	show = false;
	is_animating = false;
}

bool	PopUp::IsShowned()
{
	return (show);
}