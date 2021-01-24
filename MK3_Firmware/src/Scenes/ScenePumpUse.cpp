#include "Scenes/ScenePumpUse.h"
#include "App.h"

// *** SOME C ENUMS (to cast as uint8_t) ***
enum	PUMP_SCENE_STATE { PREPARATION, PUMP_USE, STOP, EXIT };
enum	PUMP_MODE { HARVEST_SLOW, HARVEST_MEDIUM, HARVEST_FAST, PURGE };

// *** Update Functions ***

static void	PumpHarvestSlow(tmElements_t *time)
{
	if (time->Second % 6 < 3)
		Application::singleton->ChangePump(100, 500);
	else
		Application::singleton->ChangePump(0, 500);
}

static void	PumpHarvestMedium(tmElements_t *time)
{
	if (time->Second % 6 < 4)
		Application::singleton->ChangePump(100, 500);
	else
		Application::singleton->ChangePump(0, 500);
}

static void	PumpHarvestFast(tmElements_t *time)
{
	if (time->Second % 6 < 5)
		Application::singleton->ChangePump(100, 500);
	else
		Application::singleton->ChangePump(0, 500);
}

static void	PumpPurge()
{
	Application::singleton->ChangePump(100, 500);
}

static void PumpUsageUpdate(uint8_t pump_mode)
{
	tmElements_t	time = TimeSystem::GetTime();

	switch (pump_mode)
	{
	case HARVEST_SLOW:
		PumpHarvestSlow(&time);
		break;
	case HARVEST_MEDIUM:
		PumpHarvestMedium(&time);
		break;
	case HARVEST_FAST:
		PumpHarvestFast(&time);
		break;
	case PURGE:
		PumpPurge();
		break;
	default:
		break;
	}
}

// *** Draw Functions ***

static void	PumpPreparationDraw(GraphicsEngine *graphics)
{
	graphics->Screen.textcolor = SPIRULERIE_GREY;
	graphics->Screen.drawString(TextContent::text_pump_preparation_01_FR, 80, 54);
	graphics->Screen.drawString(TextContent::text_pump_preparation_02_FR, 80, 74);

	graphics->Screen.textcolor = SPIRULERIE_RED;
	graphics->Screen.drawString(TextContent::text_start_FR, 80, 100);
}

static void	PumpUsageDraw(GraphicsEngine *graphics, uint8_t pump_mode)
{
	switch (pump_mode)
	{
	case HARVEST_SLOW:
		graphics->Screen.fillRoundRect(12, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	case HARVEST_MEDIUM:
		graphics->Screen.fillRoundRect(46, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	case HARVEST_FAST:
		graphics->Screen.fillRoundRect(82, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	case PURGE:
		graphics->Screen.fillRoundRect(116, 56, 32, 32, 4, SPIRULERIE_RED);
		break;
	default:
		break;
	}

	graphics->Screen.drawRoundRect(12, 56, 32, 32, 4, SPIRULERIE_GREEN);
	graphics->Screen.drawRoundRect(46, 56, 32, 32, 4, SPIRULERIE_GREEN);
	graphics->Screen.drawRoundRect(82, 56, 32, 32, 4, SPIRULERIE_GREEN);
	graphics->Screen.drawRoundRect(116, 56, 32, 32, 4, SPIRULERIE_GREEN);

	graphics->DrawImage(Sprites::I_32_32, 12, 56, 32, 32);
	graphics->DrawImage(Sprites::II_32_32, 46, 56, 32, 32);
	graphics->DrawImage(Sprites::III_32_32, 82, 56, 32, 32);
	graphics->DrawImage(Sprites::IV_32_32, 116, 56, 32, 32);

	graphics->Screen.textcolor = SPIRULERIE_RED;
	graphics->Screen.drawString(TextContent::text_stop_FR, 80, 100);
}

static void	PumpStopDraw(GraphicsEngine *graphics)
{
	graphics->Screen.textcolor = SPIRULERIE_GREY;
	graphics->Screen.drawString(TextContent::text_pump_stop_01_FR, 80, 64);

	graphics->Screen.textcolor = SPIRULERIE_RED;
	graphics->Screen.drawString(TextContent::text_validate_FR, 80, 100);
}

// *** Public Methods Overriding ***

void	ScenePumpUse::Initialize()
{
	Serial.printf("<== scene ScenePumpUse ==>\n");
	Scene::Initialize();

	app->pumpNominal = false; // Tell the app NOT to update the pump anymore
	app->SendAction(PWMC_D, 0, 500); // Tell the pump to stop

	// clear screen
	app->Graphics.Screen.fillSprite(SPIRULERIE_LIGHT);

	// draw title
	app->Graphics.LoadFont("Comfortaa_26", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
	app->Graphics.Screen.drawString(TextContent::text_menu_pump_FR, 80, 16);

	// Load font to use all other functions / in Draw()
	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_GREY, SPIRULERIE_LIGHT);
}

void	ScenePumpUse::OnButtonClic(BTN btn)
{
	switch (btn)
	{
	case BTN::LEFT:
		if (m_progress == PUMP_USE && m_pump_mode > HARVEST_SLOW)
			m_pump_mode--;
		break;
	case BTN::MIDDLE:
		m_progress++;
		break;
	case BTN::RIGHT:
		if (m_progress == PUMP_USE && m_pump_mode < PURGE)
			m_pump_mode++;
		break;
	default:
		break;
	}

	Scene::OnButtonClic(btn);
}

void	ScenePumpUse::Destroy()
{
	Scene::Destroy();
}

void	ScenePumpUse::Update()
{
	switch (m_progress)
	{
	case PREPARATION:
		break;
	case PUMP_USE:
		PumpUsageUpdate(m_pump_mode);
		break;
	case STOP:
		app->SendAction(PWMC_D, 0, 500);
		break;
	case EXIT:
		app->pumpNominal = true; // Give back control of the pump to the App
		app->LoadScene(new SceneMainMenu());
		break;
	default:
		break;
	}

	Scene::Update();
}

void	ScenePumpUse::Draw(GraphicsEngine *graphics)
{
	// only clean below the title
	graphics->Screen.fillRect(0, 50, 160, 78, SPIRULERIE_LIGHT);

	switch (m_progress)
	{
	case PREPARATION:
		PumpPreparationDraw(graphics);
		break;
	case PUMP_USE:
		PumpUsageDraw(graphics, m_pump_mode);
		break;
	case STOP:
		PumpStopDraw(graphics);
		break;
	case EXIT:
		break;
	default:
		break;
	}

	Scene::Draw(graphics); // push sprite to screen
}

// *** PRIVATE METHODS ***
