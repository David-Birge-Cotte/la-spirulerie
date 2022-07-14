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
	DS18B20Sensor	DS18B20Temp;

	// we should fill the queue with at least an error value. Not the undefined default
	float init_temp = -1;
	xQueueOverwrite(temperatureQueue, &init_temp);

	// more delays
	delay(1000);

	// Start the thermometer and try again if there is an error
	for (size_t i = 0; i < 10; i++)
	{
		if(DS18B20Temp.StartDevice())
			break;
		delay(400);
	}

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
			tempC = DS18B20Temp.GetTemperature();
			if (tempC == -1)
				DS18B20Temp.StartDevice();

			if (tempC < -1 || tempC == 85) //85°C is VCC disconnected
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

}

// ------------------------------
// ---------- DS18B20 -----------
// ------------------------------

DS18B20Sensor::DS18B20Sensor()
{
	oneWire = OneWire(PIN_DS18B20);
	delay(200);
	DS18B20 = DallasTemperature(&oneWire);
}

bool		DS18B20Sensor::StartDevice()
{
	DS18B20.begin();
	delay(500);
	if (!DS18B20.getAddress(adress, 0))
	{
		Serial.printf("error in starting up DS18B20..\n");
		return (false);
	}
	Serial.printf("=> DS18B20 started OK ! Adress: %u\n", adress);
	return (true);
}

float		DS18B20Sensor::GetTemperature()
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

// ------------------------------
// ---------- AM2302 ------------
// ------------------------------
/*
AM2302Sensor::AM2302Sensor() : DHTSensor(PIN_DS18B20, DHT22)
{

}

bool		AM2302Sensor::StartDevice()
{
	DHTSensor.begin();
	delay(3000);
	if (isnan(DHTSensor.readTemperature()))
	{
		Serial.printf("error in starting up AM2302..\n");
		return (false);
	}
	Serial.printf("=> AM2302 started OK !\n");
	return (true);
}

float		AM2302Sensor::GetTemperature()
{
	float tempC = DHTSensor.readTemperature();
	if(!isnan(tempC))
	{
		Serial.printf("AM2302 Value : %0.2f\n", tempC);
		return (tempC);
	}
	Serial.printf("Error reading AM2302...\n");
	return (-1);
}
*/