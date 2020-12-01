#ifndef SPIRULERIE_H
#define SPIRULERIE_H

#include <Arduino.h>
#include <DallasTemperature.h>

// ---------- ZONE EDITION UTILISATEUR -----

// version number is visible on the backside of the Spirulerie motherboard
// le numéro de version est visible sur la face arrière de la carte Spirulerie
// comment every version number except yours

//#define SPIRULERIE_104		// Spirulerie v1.4 2020
#define SPIRULERIE_105		// Spirulerie v1.5 (or 1.51) 2020
//#define SPIRULERIE_106	// Spirulerie v1.6 2021 ?

// parametres du PWM
#define PWM_FREQ			40000		// 40 khz
#define PWM_RESOLUTION_BITS	10
#define PWM_MAX_RESOLUTION	1023

// ---------- ZONE NON EDITION -------------
// PIN DEFINITIONS
#define	PIN_LCDLIGHT	17
#define PIN_DS18B20		4
#define PIN_DACBUZZER	25

#define PORT_A		12
#define PORT_B		26
#define PORT_D		27

#ifdef	SPIRULERIE_104
	#define PIN_BTN_LEFT	35
	#define PIN_BTN_MIDDLE	33
	#define PIN_BTN_RIGHT	32
	#define PORT_C  		14
#endif
#ifdef	SPIRULERIE_105
	#define PIN_BTN_LEFT	35
	#define PIN_BTN_MIDDLE	36
	#define PIN_BTN_RIGHT	39
	#define PORT_C  		16
#endif

// PWM Channels
#define PWMC_DAC	0
#define PWMC_A		1
#define PWMC_B		2
#define PWMC_C		3
#define PWMC_D		4

// ---------- Fonctions --------------------

void    SpirulerieInit();
void 	digitalPWMWrite(uint8_t channel, uint16_t duty);

#endif