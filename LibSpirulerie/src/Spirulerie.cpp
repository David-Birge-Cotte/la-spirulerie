#include "Spirulerie.h"

// Initialize the pin and pwm channel
static void	InitPWM(uint8_t channel, double frequency, uint8_t pin)
{
	pinMode(pin, OUTPUT);
	ledcSetup(channel, frequency, PWM_RESOLUTION_BITS);
	ledcAttachPin(pin, channel);
}

void    SpirulerieInit()
{
	pinMode(PIN_BTN_LEFT, INPUT); // le bouton de gauche est défini comme une entrée
	pinMode(PIN_BTN_MIDDLE, INPUT); // le bouton du milieu est défini comme une entrée
	pinMode(PIN_BTN_RIGHT, INPUT); // le bouton de droite est défini comme une entrée

	// PWM setup
	InitPWM(PWMC_A, PWM_FREQ, PORT_A);
	InitPWM(PWMC_B, PWM_FREQ, PORT_B);
	InitPWM(PWMC_C, PWM_FREQ, PORT_C);
	InitPWM(PWMC_D, PWM_FREQ, PORT_D);
}

// Outputs PWM on selected channel. duty => 0-1023
void	digitalPWMWrite(uint8_t channel, uint16_t duty)
{
	ledcWrite(channel, duty);
}
