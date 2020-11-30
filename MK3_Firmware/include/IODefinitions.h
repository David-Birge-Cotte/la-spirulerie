#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// ---------- ZONE EDITION UTILISATEUR -----

// version number is visible on the backside of the Spirulerie motherboard
// le numéro de version est visible sur la face arrière de la carte Spirulerie
// comment every version number except yours

//#define SPIRULERIE_104		// Spirulerie v1.4 2020
#define SPIRULERIE_105		// Spirulerie v1.5 (or 1.51) 2020
//#define SPIRULERIE_106	// Spirulerie v1.6 2021 ?

// ---------- ZONE NON EDITION -----
// PIN DEFINITIONS
#define	PIN_LCDLIGHT	17

#define PIN_12V_A		12
#define PIN_12V_B		26
#define PIN_12V_D		27

#define PIN_DS18B20		4

#define PIN_DACBUZZER	25

#ifdef	SPIRULERIE_104
	#define PIN_BTN_LEFT	35
	#define PIN_BTN_MIDDLE	33
	#define PIN_BTN_RIGHT	32
	#define PIN_12V_C		14
#endif
#ifdef	SPIRULERIE_105
	#define PIN_BTN_LEFT	35
	#define PIN_BTN_MIDDLE	36
	#define PIN_BTN_RIGHT	39
	#define PIN_12V_C		16
#endif

// PWM Channels
#define PWMC_DAC		0
#define PWMC_IO_A		1
#define PWMC_IO_B		2
#define PWMC_IO_C		3
#define PWMC_IO_D		4
#define	PWMC_BRIGHTNESS	5

#endif