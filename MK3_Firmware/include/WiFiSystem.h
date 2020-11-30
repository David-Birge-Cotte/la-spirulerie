#ifndef WIFI_SYSTEM_H
#define WIFI_SYSTEM_H

#include "Arduino.h"
#include "WiFi.h"
#include "DNSServer.h"

#define DNS_PORT	53

class WiFiSystem
{
	public:
		// Methods
		WiFiSystem();
		void		Start();
		void		Stop();
		void		Update();

	private:
		// Members
		WiFiServer	m_wifiServer;
		//DNSServer	m_dnsServer;
		IPAddress	m_apIP;
};

#endif