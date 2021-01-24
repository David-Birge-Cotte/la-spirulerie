#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <TFT_eSPI.h>
#include "SpriteArrays.h"

#define WIN_WIDTH	160
#define WIN_HEIGHT	128

// La Spirulerie's color scheme in RGB 565
#define	SPIRULERIE_GREEN	0x2C6B
#define	SPIRULERIE_BLUE		0x7D57
#define	SPIRULERIE_RED		0xE904
#define	SPIRULERIE_LIGHT	0xEFBE
#define	SPIRULERIE_GREY		0x2965

class GraphicsEngine
{
	public:
		TFT_eSPI	TftSPI;
		TFT_eSprite	Screen;
		GraphicsEngine();
		void	Init();
		void	PushToScreen();
		void	LoadFont(String font_name, uint32_t font_color, uint32_t bg_color);

		// DRAW ROUTINES
		void	DrawScreen(uint32_t color);
		void	DrawImage(const uint16_t *color_array, int16_t x, int16_t y, uint16_t w, uint16_t h);
		void	DrawProgressBar(uint8_t progress, 
				int32_t x, int32_t y, int32_t width, int32_t height,
				uint32_t color_bg, uint32_t color_progress);
		void	DrawRightArrow();
		void	DrawLeftArrow();
};

#endif