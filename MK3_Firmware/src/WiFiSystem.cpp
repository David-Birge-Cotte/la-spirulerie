#include "WiFiSystem.h"

WiFiSystem::WiFiSystem() :
	m_wifiServer(80)
{

}

void	WiFiSystem::Start()
{
	Serial.printf("- Wifi System init ...");

	WiFi.softAP("La Spirulerie wifi");
	m_apIP = WiFi.softAPIP();

	Serial.print("AP IP address: ");
	Serial.println(m_apIP);

	m_wifiServer.begin();
}

void	WiFiSystem::Stop()
{
	WiFi.softAPdisconnect();
	m_wifiServer.stop();
}

void	WiFiSystem::Update()
{
	WiFiClient client = m_wifiServer.available();

	if (client)
	{
		Serial.printf("Client is connected\n");
		client.println("<!DOCTYPE html><html><h1>La Spirulerie Super Website !</h1></html>");
	}
}