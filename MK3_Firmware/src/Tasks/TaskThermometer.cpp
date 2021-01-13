#include "Tasks/TaskThermometer.h"

TaskHandle_t	InitThermometer()
{
	TaskHandle_t	handle;

	#ifdef SERIAL_DEBUG
		Serial.println("- Thermometer init ..");
	#endif

	xTaskCreate(
		ThermometerTask, "Thermometer task", 2048, NULL, 3, &handle);

	return (handle);
}

void		ThermometerTask(void *parameter)
{
	QueueHandle_t	temperatureQueue = Application::singleton->temperatureQueue;
	QueueHandle_t	TSensorActiveQueue = Application::singleton->TSensorActiveQueue;
	Thermometer		thermometer;

	// we should fill the queue with at least an error value. Not the undefined default
	float init_temp = -1;
	xQueueOverwrite(temperatureQueue, &init_temp);

	// more delays
	delay(1000);

	// Start the thermometer and try again if there is an error
	while (!thermometer.StartDevice())
		delay(400);

	// Wait a bit between initialization and first reading
	delay(5000);

	// Read termperature and send it in to the RTOS queue
	for (;;)
	{
		float	tempC = -1;
		bool	canCheckTemperature = false;

		// Check if authorized to get temperature (because its freezes for a few milliseconds)
		xQueuePeek(TSensorActiveQueue, &canCheckTemperature, 10);
		if (canCheckTemperature)
		{
			// Check Temperature
			tempC = thermometer.GetTemperature();
			if (tempC == -1)
				thermometer.StartDevice();

			if (tempC < -1)
				tempC = -1; // sometime gets -127 for some reason

			// Send temperature to Queue
			xQueueOverwrite(temperatureQueue, &tempC);
		}
		if (tempC != -1)
			delay(READING_DELAY);
		else
			delay(2000);
	}
}

Thermometer::Thermometer()
{
	oneWire = OneWire(PIN_DS18B20);
	delay(200);
	DS18B20 = DallasTemperature(&oneWire);
}

bool		Thermometer::StartDevice()
{
	DS18B20.begin();
	delay(500);
	if (!DS18B20.getAddress(adress, 0))
	{
		Serial.printf("error in starting up DS18B20..\n");
		return (false);
	}
	Serial.printf("=> DS18B20 started OK !\n");
	return (true);
}

float		Thermometer::GetTemperature()
{
	if (DS18B20.requestTemperaturesByAddress(adress))
	{
		delay(2000); // A DELAY IS NEEDED between temperature request and getTempC
		float tempC = DS18B20.getTempC(adress);
		Serial.printf("DS18B20 Value : %0.2f\n", tempC);
		return (tempC);
	}
	Serial.printf("Error getting adress temperature...\n");
	return (-1);
}