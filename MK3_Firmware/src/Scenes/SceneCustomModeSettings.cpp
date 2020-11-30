#include "Scenes/SceneCustomModeSettings.h"
#include "App.h"

enum PARAMS { LUMIERE_MAX, HOUR_START, HOUR_END, T_DAY, T_NIGHT, PUMP_CYCLE_PER_HOUR, PUMP_CYCLE_LENGHT };

void	SceneCustomModeSettings::Initialize()
{
	Serial.printf("<== scene SceneCustomModeSelection ==>\n");
	Scene::Initialize();

	m_custom_mode = DataSaveLoad::ReadCustomMode();
	m_selection = (float)(100.0f / MAX_PERCENTAGE_LIGHT) * m_custom_mode.light_max;

	app->Graphics.LoadFont("Comfortaa_16", SPIRULERIE_BLUE, SPIRULERIE_LIGHT);
	app->Graphics.Screen.setTextDatum(TC_DATUM);
}

void	SceneCustomModeSettings::Update()
{
	Scene::Update();

	switch (m_progress)
	{
	case PARAMS::LUMIERE_MAX:
		if (m_selection > 100)
			m_selection = 0;
		if (m_selection < 0)
			m_selection = 100;

		m_title_text = TextContent::text_custom_mode_title_light_FR;
		m_helper_text = TextContent::text_custom_mode_light_max_FR;
		m_selection_text = (String)m_selection + " %";
		break;
	case PARAMS::HOUR_START:
		if (m_selection > 11)
			m_selection = 11;
		if (m_selection < 0)
			m_selection = 0;

		m_title_text = TextContent::text_custom_mode_title_day_FR;
		m_helper_text = TextContent::text_custom_mode_day_start_FR;
		m_selection_text = (String)m_selection + " h";
		break;
	case PARAMS::HOUR_END:
		if (m_selection > 23)
			m_selection = 23;
		if (m_selection < 12)
			m_selection = 12;

		m_helper_text = TextContent::text_custom_mode_day_stop_FR;
		m_selection_text = (String)m_selection + " h";
		break;
	case PARAMS::T_DAY:
		if (m_selection > 38)
			m_selection = 38;
		if (m_selection < 0)
			m_selection = 0;

		m_title_text = TextContent::text_custom_mode_title_temperature_FR;
		m_helper_text = TextContent::text_custom_mode_temperature_day_FR;
		m_selection_text = (String)m_selection + " °C";
		break;
	case PARAMS::T_NIGHT:
		if (m_selection > 38)
			m_selection = 38;
		if (m_selection < 0)
			m_selection = 0;

		m_helper_text = TextContent::text_custom_mode_temperature_night_FR;
		m_selection_text = (String)m_selection + " °C";
		break;
	case PARAMS::PUMP_CYCLE_PER_HOUR:
		if (m_selection > 30)
			m_selection = 0;
		if (m_selection < 0)
			m_selection = 30;

		m_title_text = TextContent::text_custom_mode_title_pump_FR;
		m_helper_text = TextContent::text_custom_mode_pump_cycles_per_hour_FR;
		m_selection_text = (String)m_selection + " par h";
		break;
	case PARAMS::PUMP_CYCLE_LENGHT:
		if (m_selection > 120)
			m_selection = 0;
		if (m_selection < 0)
			m_selection = 120;

		m_helper_text = TextContent::text_custom_mode_pump_cycle_lenght_FR;
		m_selection_text = (String)m_selection + " sec";
		break;
	default:
		break;
	}
}

void	SceneCustomModeSettings::Draw(GraphicsEngine *graphics)
{
	graphics->DrawScreen(SPIRULERIE_LIGHT);

	// draw upper text
	graphics->Screen.textcolor = SPIRULERIE_BLUE;
	graphics->Screen.drawString(m_title_text, 80, 10);
	graphics->Screen.textcolor = SPIRULERIE_GREEN;
	graphics->Screen.drawString(m_helper_text, 80, 28);

	// draw value and arrows
	graphics->Screen.textcolor = SPIRULERIE_RED;
	graphics->Screen.drawString(m_selection_text, 80, 60);
	graphics->DrawLeftArrow();
	graphics->DrawRightArrow();

	// draw exit text
	graphics->Screen.textcolor = SPIRULERIE_RED;
	if (m_progress == PARAMS::PUMP_CYCLE_LENGHT)
		graphics->Screen.drawString(TextContent::text_validate_FR, 80, 100);
	else
		graphics->Screen.drawString(TextContent::text_select_FR, 80, 100);

	Scene::Draw(graphics); // push sprite to screen
}

void	SceneCustomModeSettings::OnButtonClic(BTN btn)
{
	Scene::OnButtonClic(btn);
	
	switch (btn)
	{
	case BTN::LEFT:
		// decrease value of selected option
		m_selection--;
		break;
	case BTN::MIDDLE:
		// get to next option
		m_progress++;
		if (m_progress == PARAMS::HOUR_START)
		{
			m_custom_mode.light_max = m_selection*MAX_PERCENTAGE_LIGHT/100;
			m_selection = m_custom_mode.hour_dawn;
		}	
		else if (m_progress == PARAMS::HOUR_END)
		{
			m_custom_mode.hour_dawn = m_selection;
			m_selection = m_custom_mode.hour_dusk;
		}
		else if (m_progress == PARAMS::T_DAY)
		{
			m_custom_mode.hour_dusk = m_selection;
			m_selection = m_custom_mode.temperature_day;
		}
		else if (m_progress == PARAMS::T_NIGHT)
		{
			m_custom_mode.temperature_day = m_selection;
			m_selection = m_custom_mode.temperature_night;
		}
		else if (m_progress == PARAMS::PUMP_CYCLE_PER_HOUR)
		{
			m_custom_mode.temperature_night = m_selection;
			m_selection = m_custom_mode.pump_cycles_per_hour;
		}
		else if (m_progress == PARAMS::PUMP_CYCLE_LENGHT)
		{
			m_custom_mode.pump_cycles_per_hour = m_selection;
			m_selection = m_custom_mode.pump_cycle_lenght;
		}
		else
		{
			m_custom_mode.pump_cycle_lenght = m_selection;
			Validate(); // exit
		}
		break;
	case BTN::RIGHT:
		// increase value of selected option
		m_selection++;
		break;
	default:
		break;
	}
}

void	SceneCustomModeSettings::Destroy()
{
	Scene::Destroy();
}

// *** PRIVATE METHODS ***
void	SceneCustomModeSettings::Validate()
{
	// TODO save mode to EEPROM
	DataSaveLoad::SetCustomMode(m_custom_mode);
	app->modeNeedsRefresh = true;
	app->LoadScene(new SceneMainMenu());
}