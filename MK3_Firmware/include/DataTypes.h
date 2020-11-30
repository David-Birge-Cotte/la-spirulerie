#ifndef	DATA_TYPES_H
#define	DATA_TYPES_H

#include <Arduino.h>

enum class BTN { NONE, LEFT, MIDDLE, RIGHT };
enum class Melodies { BOOT, VALID, ERROR };

struct BtnEvent
{
	BTN		btn;
	bool	isPressed; // on press = true, on release = false
};

// Stores the parameters associated with a mode
struct ModeParameters
{
	// Lighting data
	uint8_t	light_max;	// max day light in percentage 0-100%
	uint8_t	hour_dusk;	// hour at which the day starts
	uint8_t	hour_dawn;	// hour at which the night starts

	// Heating data
	uint8_t	temperature_day;
	uint8_t temperature_night;

	// Agitation data
	uint8_t	pump_cycles_per_hour; // MAXIMUM 30
	uint8_t	pump_cycle_lenght; // MAXIMUM 120 (in seconds)

	ModeParameters();
	ModeParameters(uint8_t	light_max, uint8_t	hour_dusk, uint8_t	hour_dawn, 
			uint8_t	temperature_day, uint8_t	temperature_night,
			uint8_t	pump_cycles_per_hour, uint8_t	pump_cycle_lenght);
};

#endif