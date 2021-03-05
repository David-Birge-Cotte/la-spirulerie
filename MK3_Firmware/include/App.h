#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include <Spirulerie.h>

#include "DataTypes.h"
#include "SPIFFS.h"
#include "TimeSystem.h"
#include "TextContent.h"
#include "DataSaveLoad.h"

#include "WiFiSystem.h"

#include "Tasks/TaskActuators.h"
#include "Tasks/TaskThermometer.h"
#include "Tasks/TaskAudioEngine.h"
#include "Tasks/TaskInput.h"
#include "Tasks/TaskApplication.h"

#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/SimplexNoise.h"
#include "GraphicsEngine/SpriteArrays.h"
#include "GraphicsEngine/Elements.h"

#include "Scenes/Scene.h"
#include "Scenes/SceneMainMenu.h"
#include "Scenes/SceneLoadingScreen.h"
#include "Scenes/SceneTopMenu.h"
#include "Scenes/ScenePumpUse.h"
#include "Scenes/SceneModeSelection.h"
#include "Scenes/SceneCustomModeSettings.h"
#include "Scenes/SceneSettingsMenu.h"
#include "Scenes/SceneTime.h"
#include "Scenes/SceneThermometerCalibration.h"
#include "Scenes/SceneHeatingSettings.h"
#include "Scenes/SceneScreenSaverSettings.h"
#include "Scenes/TestScene.h"

// Commenting options
#define	SERIAL_DEBUG // TODO faudrait l'implémenter car les serial debug sont par default partout...
//#define	RESET_EEPROM_AT_BOOT // utile pour reset une carte quand on a modifié la partition d'EEPROM

// Defines
#define	MAX_PERCENTAGE_LIGHT	35	// do not go above this value or the LED will fail (burn, melt plastic etc...)
#define	MAX_PERCENTAGE_HEATER	75	// So it doesn't draw too much current
#define	SECONDS_TO_SCREENSAVER	45	// only if screensaver is enabled in settings

// Main container class for program
class Application
{
	// *** PUBLIC MEMBERS ***
	public:
		// Singleton
		static Application	*singleton;

		// Member classes
		GraphicsEngine	Graphics;
		WiFiSystem		WifiSystem;

		// RTOS Queues
		QueueHandle_t	temperatureQueue;
		QueueHandle_t	TSensorActiveQueue;
		QueueHandle_t	PWMActionsQueue;
		QueueHandle_t	inputQueue;
		QueueHandle_t	audioQueue;

		// RTOS Tasks
		TaskHandle_t	audioTask;
		TaskHandle_t	thermometerTask;
		TaskHandle_t	actuatorTask;
		TaskHandle_t	applicationTask;
		TaskHandle_t	inputManagementTask;

		// App will control the actuators if true
		bool			lightNominal = true;
		bool			heatNominal = true;
		bool			pumpNominal = true;
		bool			isOnMainMenu = true;

		bool				modeNeedsRefresh = true;
		ModeParameters		parameters;

	// *** PUBLIC METHODS ***
	public:
		// Constructor
		Application();
		void	Init();
		void	Update();

		// Retrieve obfuscated data
		float	GetCurrentTemperature();
		float	GetCurrentLightLevel();
		bool	GetPumpState();

		void	LoadScene(Scene *scene);

		// Intertask communication
		void	SendAction(uint8_t PWMChannel, float percentage, uint32_t fadetime);
		void	PlayMelody(Melodies melody);
		void	ChangeLight(uint8_t percentage_A, uint8_t percentage_B, uint32_t fade_time);
		void	ChangePump(uint8_t percentage, uint32_t fadetime);

	// *** PRIVATE METHODS ***
	private:
		// Actuator management
		void	Lighting();
		void	Heating();
		void	Pump();
		void	StopHeating();

		// Booleans test
		bool	IsDay();
		bool	IsDebouncedInput(BTN btn);

	// *** PRIVATE MEMBERS ***
	private:
		Scene			*m_current_scene;
		uint8_t			m_current_pump_level = 0;
		uint8_t			m_current_light_level = 0;
		float			m_current_temperature = -1;
		uint64_t		m_last_btn_press_time = 0;
		bool			m_is_in_screensaver = false;
		ModeParameters	m_mode_hibernation;
		ModeParameters	m_mode_normal;
};

#endif