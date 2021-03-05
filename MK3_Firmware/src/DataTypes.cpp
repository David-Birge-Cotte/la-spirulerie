#include "DataTypes.h"

ModeParameters::ModeParameters()
{
	this->light_max_A = 31;
	this->light_max_B = 15;
	this->hour_dusk = 23;
	this->hour_dawn = 5;
	this->temperature_day = 35;
	this->temperature_night = 28;
	this->pump_cycles_per_hour = 7;
	this->pump_cycle_lenght = 45;
}

ModeParameters::ModeParameters(
	uint8_t	light_max_A, uint8_t light_max_B, uint8_t	hour_dusk, uint8_t	hour_dawn,
	uint8_t	temperature_day, uint8_t	temperature_night,
	uint8_t	pump_cycles_per_hour, uint8_t	pump_cycle_lenght)
{
	this->light_max_A = light_max_A;
	this->light_max_B = light_max_B;
	this->hour_dusk = hour_dusk;
	this->hour_dawn = hour_dawn;
	this->temperature_day = temperature_day;
	this->temperature_night = temperature_night;
	this->pump_cycles_per_hour = pump_cycles_per_hour;
	this->pump_cycle_lenght = pump_cycle_lenght;
}