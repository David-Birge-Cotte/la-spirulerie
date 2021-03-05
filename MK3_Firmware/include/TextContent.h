#ifndef TEXT_CONTENT_H
#define TEXT_CONTENT_H

#include <pgmspace.h>

namespace TextContent
{
	const char	text_title[] PROGMEM = "La Spirulerie";

	// ********** FRENCH TEXT ********** //
	// **** MENUS ****
	const char	text_menu_pump_FR[] PROGMEM		= "pompe";
	const char	text_menu_mode_FR[] PROGMEM		= "mode";
	const char	text_menu_settings_FR[] PROGMEM	= "réglages";
	const char	text_menu_games_FR[] PROGMEM	= "jeux";
	const char	text_menu_time_FR[] PROGMEM		= "heure";
	const char	text_menu_therm_FR[] PROGMEM	= "thermomètre";

	// **** PUMP ****
	const char	text_pump_preparation_01_FR[] = "> préparer le tube";
	const char	text_pump_preparation_02_FR[] = "> et autre matériel";

	const char	text_pump_stop_01_FR[] = "> replacer tube";

	// **** RECOLTE ****
	const char	text_harvest_00_FR[] PROGMEM = "> préparer le tube";
	const char	text_harvest_01_FR[] PROGMEM = "> préparer le filtre";
	const char	text_harvest_10_FR[] PROGMEM = "récolte en cours";
	const char	text_harvest_20_FR[] PROGMEM = "> presser filtre";
	const char	text_harvest_21_FR[] PROGMEM = "> spiruline 0-5°C";

	// **** PURGE ****
	const char	text_purge_00_FR[] PROGMEM	= "> préparer le tube";
	const char	text_purge_10_FR[] PROGMEM	= "purge en cours";
	const char	text_purge_20_FR[] PROGMEM	= "> replacer le tube";

	// **** THERMOMETRE ****
	const char	text_therm_calibration_FR[] PROGMEM = "écart de T en C°";

	// **** CHAUFFAGE ****
	const char	text_chauffage_puissance_FR[] PROGMEM = "puissance";

	// **** VEILLE ****
	const char	text_veille_actif_FR[] PROGMEM = "écran veille ?";

	// **** MENU PARAMETRE ****
	const char	text_settings_heure_FR[] PROGMEM = "heure";
	const char	text_settings_therm_FR[] PROGMEM = "thermomètre";
	const char	text_settings_chauffage[] PROGMEM = "chauffage";
	const char	text_settings_veille[] PROGMEM = "veille";

	// **** MODES
	const char	text_mode_hibernation_FR[] PROGMEM = "hibernation";
	const char	text_mode_normal_FR[] PROGMEM = "normal";
	const char	text_mode_custom_FR[] PROGMEM = "personnalisé";

	// **** MODE CUSTOMISATION
	const char	text_custom_mode_title_light_A_FR[] PROGMEM = "lumière 1";
	const char	text_custom_mode_title_light_B_FR[] PROGMEM = "lumière 2";
	const char	text_custom_mode_title_day_FR[] PROGMEM = "journée";
	const char	text_custom_mode_title_temperature_FR[] PROGMEM = "température";
	const char	text_custom_mode_title_pump_FR[] PROGMEM = "pompe";

	const char	text_custom_mode_light_max_FR[] PROGMEM = "puissance max";
	const char	text_custom_mode_day_start_FR[] PROGMEM = "début du jour";
	const char	text_custom_mode_day_stop_FR[] PROGMEM = "fin du jour";
	const char	text_custom_mode_temperature_day_FR[] PROGMEM = "en journée";
	const char	text_custom_mode_temperature_night_FR[] PROGMEM = "la nuit";
	const char	text_custom_mode_pump_cycles_per_hour_FR[] PROGMEM = "nombre de cycles";
	const char	text_custom_mode_pump_cycle_lenght_FR[] PROGMEM = "durée du cycle";

	// **** GENERAL ****
	const char	text_start_FR[] PROGMEM		= "[commencer]";
	const char	text_stop_FR[] PROGMEM		= "[arreter]";
	const char	text_validate_FR[] PROGMEM	= "[valider]";
	const char	text_select_FR[] PROGMEM	= "[selectionner]";
	const char	text_oui_FR[] PROGMEM		= "oui";
	const char	text_non_FR[] PROGMEM		= "non";
}

#endif