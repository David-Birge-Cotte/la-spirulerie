#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <Arduino.h>
#include <Spirulerie.h>

#include "App.h"
//#include "Adafruit_Sensor.h"
//#include "DHT.h"

#define READING_DELAY	3000 //30000

class Thermometer
{
	public:	
		// Methods
		Thermometer();
		virtual bool		StartDevice();
		virtual float		GetTemperature();
};

class DS18B20Sensor : Thermometer
{
	protected:
		OneWire				oneWire;
		DallasTemperature	DS18B20;
		DeviceAddress		adress;

	public:	
		DS18B20Sensor();
		bool  			StartDevice() override;
		float			GetTemperature() override;
};

/*
class AM2302Sensor : Thermometer
{
	protected:
		DHT				DHTSensor;

	public:	
		AM2302Sensor();
		bool  			StartDevice() override;
		float			GetTemperature() override;
};
*/

// Functions
TaskHandle_t	InitThermometer(); // entry point
void			ThermometerTask(void *parameter); // RTOS task loop

#endif