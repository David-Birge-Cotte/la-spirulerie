#include <Arduino.h>
#include "App.h"

Application App; // Global Application class with singleton reference

void setup()
{
	#ifdef SERIAL_DEBUG
		// Start serial connexion
		Serial.begin(112500);
		delay(1000); // wait for serial to connect
	#endif

	InitApplication(); // Starts the program
}

void loop()
{
	// program is done in tasks
}
