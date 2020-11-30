#include "GraphicsEngine/GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
	: TftSPI(), Screen(&TftSPI)
{

}

void	GraphicsEngine::Init()
{
	TftSPI.init();
	TftSPI.setRotation(3);
	TftSPI.fillScreen(TFT_BLACK);

	Screen.setColorDepth(16); // or 8 ??
	Screen.createSprite(WIN_WIDTH, WIN_HEIGHT);

	Screen.textcolor = TFT_WHITE;
	Screen.textbgcolor = TFT_BLACK;
}

void	GraphicsEngine::PushToScreen()
{
	Screen.pushSprite(0, 0);
}

void	GraphicsEngine::LoadFont(String font_name, uint32_t font_color, uint32_t bg_color)
{
	Screen.loadFont(font_name);
	Screen.setTextColor(font_color);
	Screen.textbgcolor = bg_color;
}

void	GraphicsEngine::DrawScreen(uint32_t color)
{
	Screen.fillSprite(color);
}

void	GraphicsEngine::DrawImage(const uint16_t *color_array, int16_t x, int16_t y, uint16_t w, uint16_t h)
{
	uint32_t i = 0;
	for (uint16_t y_ = 0; y_ < h; y_++)
	{
		for (uint16_t x_ = 0; x_ < w; x_++)
		{
			uint16_t c = color_array[i];
			if (c != 0xffff) // white == transparent
				Screen.drawPixel(x_ + x, y_ + y, color_array[i]);
			i++;
		}
	}
}

void	GraphicsEngine::DrawProgressBar(uint8_t progress, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color_bg, uint32_t color_progress)
{
	int32_t	progress_width = w * progress / 100;

	Screen.fillRect(x, y, w, h, color_bg);
	Screen.fillRect(x, y, progress_width, h, color_progress);
}

void	GraphicsEngine::DrawRightArrow()
{
	Screen.fillRect(138, 62, 10, 5, TFT_WHITE);
	Screen.fillTriangle(148, 56, 148, 72, 156, 64, TFT_WHITE);
}

void	GraphicsEngine::DrawLeftArrow()
{
	Screen.fillRect(12, 62, 10, 5, TFT_WHITE);
	Screen.fillTriangle(12, 56, 12, 72, 4, 64, TFT_WHITE);
}
