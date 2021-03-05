#include "App.h"

// Singleton needs to be implementated to nullptr default. C++...
Application* Application::singleton = nullptr;

Application::Application()
{
	// Only one App in the project. Dont override, dont allocate a new App()
	singleton = this;

	m_mode_normal = ModeParameters();
	m_mode_hibernation = ModeParameters(10, 5, 21, 7, 22, 20, 10, 45);
}

void Application::Init()
{
	// Init RTOS queues
	temperatureQueue = xQueueCreate(1, sizeof(float));
	TSensorActiveQueue = xQueueCreate(1, sizeof(bool));
	PWMActionsQueue = xQueueCreate(20, sizeof(ActuatorPWMAction));
	inputQueue = xQueueCreate(5, sizeof(BtnEvent));
	audioQueue = xQueueCreate(5, sizeof(Melodies));

	// Init RTOS tasks
	audioTask = InitAudio();
	thermometerTask = InitThermometer();
	actuatorTask = InitActuators();
	inputManagementTask = InitInputManagement();
	
	// Initialize some other stuff

	SPIFFS.begin(true);
	TimeSystem::ResetToFactoryTime();
	Graphics.Init();

	// start screen
	pinMode(PIN_LCDLIGHT, OUTPUT);
	digitalWrite(PIN_LCDLIGHT, HIGH);

	// TODO put in screen for it
	//WifiSystem.Start();

	DataSaveLoad::InitEEPROM();
	#ifdef RESET_EEPROM_AT_BOOT
	DataSaveLoad::Clear();
	#endif
	if (DataSaveLoad::ReadDeviceInitialized() == false)
	{
		Serial.printf("***\nDEVICE NOT INITIALIZED !! first boot ? -> setting up EEPROM...\n***\n");
		DataSaveLoad::Clear();
		DataSaveLoad::SetDeviceInitialized(true);
	}

	uint64_t boot_nb = DataSaveLoad::ReadBootNb() + 1;
	DataSaveLoad::SetBootNb(boot_nb);
	Serial.printf("bootNumber: %d\n", boot_nb);

	LoadScene(new SceneLoadingScreen());
}

void Application::Update()
{
	// ******** App Functions ********

	// authorize temperature reading only on main menu
	xQueueOverwrite(TSensorActiveQueue, &isOnMainMenu);

	if (modeNeedsRefresh)
	{
		uint8_t mode = DataSaveLoad::ReadCurrentMode();
		if (mode == 0)
			parameters = m_mode_hibernation;
		else if (mode == 1)
			parameters = m_mode_normal;
		else if (mode == 2)
			parameters = DataSaveLoad::ReadCustomMode();
		Serial.printf("NEW MODE luminosity: %d\n", parameters.light_max_A);
		modeNeedsRefresh = false;
	}

	// Control the actuators
	if (lightNominal)
		Lighting();
	if (heatNominal)
		Heating();
	if (pumpNominal)
		Pump();

	if (isOnMainMenu && DataSaveLoad::ReadCanScreenSave() && !m_is_in_screensaver
			&& (millis() - m_last_btn_press_time) / 1000 > SECONDS_TO_SCREENSAVER)
		{
			digitalWrite(PIN_LCDLIGHT, LOW);
			m_is_in_screensaver = true;
		}

	// ******** SCENE Functions ********
	// Handle input events and call the current scene's OnButtonClic() function
	BtnEvent btnEvent;
	if (xQueueReceive(inputQueue, &btnEvent.btn, 0))
	{
		if (m_is_in_screensaver)
			digitalWrite(PIN_LCDLIGHT, HIGH);
		m_last_btn_press_time = millis();
		m_is_in_screensaver = false;

		if (btnEvent.isPressed == true && IsDebouncedInput(btnEvent.btn))
			m_current_scene->OnButtonClic(btnEvent.btn);
	}
	// Update() logic and Draw() the current scene to the screen
	m_current_scene->Update();
	m_current_scene->Draw(&Graphics);

	// ******** RTOS ********
	// Dont monopolise resources
	delay(1);
}

// ************************************************************************* //
// Data getters
// ************************************************************************* //

float	Application::GetCurrentTemperature()
{
	float	temperatureC;
	xQueuePeek(temperatureQueue, &temperatureC, 0);
	if (temperatureC == -1 && m_current_temperature != -1)
		return (m_current_temperature);
	return (temperatureC + DataSaveLoad::ReadThermometerAdjustement());
}

float	Application::GetCurrentLightLevel()
{
	return (m_current_light_level);
}

bool	Application::GetPumpState()
{
	if (m_current_pump_level == 0)
		return (false);
	return (true);
}

bool	Application::IsDay()
{
	tmElements_t current_time = TimeSystem::GetTime();
	if (current_time.Hour > parameters.hour_dawn &&
		current_time.Hour < parameters.hour_dusk)
		return (true);
	return (false);
}

// ************************************************************************* //

void	Application::LoadScene(Scene *scene)
{
	if (m_current_scene != nullptr)
	{
		m_current_scene->Destroy();
		delete (m_current_scene); // hope there is no memory shananigans with inheritance
	}
	m_current_scene = scene;
	m_current_scene->Initialize();
	m_current_scene->Update();
}

// ************************************************************************* //
// Actuator management
// ************************************************************************* //

void Application::Lighting()
{
	uint8_t light_value_A = 0;
	uint8_t	light_value_B = 0;
	tmElements_t current_time = TimeSystem::GetTime();

	if (current_time.Hour > parameters.hour_dawn
		&& current_time.Hour < parameters.hour_dusk)
	{
		// TODO could be refactored more elegantly and with a smoother gradient
		light_value_A = parameters.light_max_A;
		if (current_time.Hour - parameters.hour_dawn == 0)
			light_value_A = parameters.light_max_A / 3;
		else if (current_time.Hour - parameters.hour_dusk == 1)
			light_value_A = parameters.light_max_A / 2;

		if (parameters.hour_dawn - current_time.Hour == 0)
			light_value_A = parameters.light_max_A / 3;
		else if (parameters.hour_dusk - current_time.Hour == 1)
			light_value_A = parameters.light_max_A / 2;

		// TODO could be refactored more elegantly and with a smoother gradient
		light_value_B = parameters.light_max_B;
		if (current_time.Hour - parameters.hour_dawn == 0)
			light_value_B = parameters.light_max_B / 3;
		else if (current_time.Hour - parameters.hour_dusk == 1)
			light_value_B = parameters.light_max_B / 2;

		if (parameters.hour_dawn - current_time.Hour == 0)
			light_value_B = parameters.light_max_B / 3;
		else if (parameters.hour_dusk - current_time.Hour == 1)
			light_value_B = parameters.light_max_B / 2;
	}

	ChangeLight(light_value_A, light_value_B, 1500);
}

void Application::Heating()
{
	float temperature = GetCurrentTemperature();

	static uint64_t first_try = 0;
	if (temperature == -1) // if there is a problem with the temperature
	{
		// stores the timing of the first reading problem
		if (first_try == 0)
			first_try = millis();

		if (millis() - first_try > 15000)	// if the problem persists for too long
			m_current_temperature = -1;		// App needs to know out of the scope of this function
	}
	else
	{
		first_try = 0; // resets the timing storage for next time
		m_current_temperature = temperature; // update the stored temperature
	}

	if (temperature == -1)
	{
		// Do not turn on the heating if the thermometer is not working
		StopHeating();
		return;
	}


	uint8_t pourcentage_chauffage = DataSaveLoad::ReadCurrentHeatingPercentage();
	
	if (IsDay())
	{
		if (temperature < parameters.temperature_day)
			SendAction(PWMC_C, pourcentage_chauffage, 1000);
		else
			StopHeating();
	}
	else
	{
		if (temperature < parameters.temperature_night)
			SendAction(PWMC_C, pourcentage_chauffage, 0);
		else
			StopHeating();
	}
}

void	Application::StopHeating()
{
	SendAction(PWMC_C, 0, 1000);
}

void	Application::Pump()
{
	tmElements_t 	time;
	uint8_t			cycle_delay;
	float			cycle_time_minutes;
	uint8_t			cycle_current_minute;

	if (parameters.pump_cycles_per_hour == 0)
	{
		ChangePump(0, 600);
		return;
	}

	time = TimeSystem::GetTime();
	cycle_delay = 60 / parameters.pump_cycles_per_hour;
	cycle_time_minutes = parameters.pump_cycle_lenght / 60;
	cycle_current_minute = time.Minute % cycle_delay;
	
	if (cycle_current_minute < cycle_time_minutes)
	{
		ChangePump(100, 1000);
		return;
	}
	else if (cycle_current_minute == (uint8_t)cycle_time_minutes)
	{
		// getting the number of seconds in the last minute
		uint8_t seconds = 
			parameters.pump_cycle_lenght - (60 * (uint8_t)cycle_time_minutes);

		if (time.Second <= seconds)
		{
			ChangePump(100, 1000);
			return;
		}
	}
	ChangePump(0, 600);
}

// ************************************************************************* //
// Input
// ************************************************************************* //

// Checks the potential bouncing of the button press.
// Returns true if the input is valid (not a bounce), false otherwise
bool Application::IsDebouncedInput(BTN btn)
{
	static uint64_t	lastmillis = 0;
	static BTN		lastBTN = BTN::NONE;

	uint64_t currentmillis = millis();
	if (btn != lastBTN || currentmillis - lastmillis > 100)
	{
		lastBTN = btn;
		lastmillis = currentmillis;
		return (true);
	}
	return (false);
}

// ************************************************************************* //
// Intertask communication
// ************************************************************************* //

void Application::SendAction(uint8_t PWMChannel, float percentage, uint32_t fadetime)
{
	ActuatorPWMAction action = { PWMChannel, percentage, fadetime };
	xQueueSend(PWMActionsQueue, &action, 0);
}

void Application::PlayMelody(Melodies melody)
{
	xQueueSend(audioQueue, &melody, 0);
}

void	Application::ChangeLight(uint8_t percentage_A, uint8_t percentage_C, uint32_t fade_time)
{
	if (percentage_A > 100)
		percentage_A = 100;
	if (percentage_C > 100)
		percentage_C = 100;

	if (m_current_light_level != percentage_A)
	{
		SendAction(PWMC_A, percentage_A, fade_time);	// Warm White LED
		SendAction(PWMC_B, percentage_C, fade_time);	// Red LED (heats more -> decrease pwm)
	}
	m_current_light_level = percentage_A;
}

void	Application::ChangePump(uint8_t percentage, uint32_t fade_time)
{
	if (percentage > 100)
		percentage = 100;

	if (m_current_pump_level != percentage)
	{
		SendAction(PWMC_D, percentage, fade_time);
	}
	m_current_pump_level = percentage;
}