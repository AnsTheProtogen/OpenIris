#pragma once
#ifndef WIFIHANDLER_HPP
#define WIFIHANDLER_HPP
#include <memory>
#include <string>
#include <WiFi.h>
#include "data/StateManager/StateManager.hpp"
#include "data/config/project_config.hpp"
#include "data/utilities/helpers.hpp"

class WiFiHandler
{
public:
	WiFiHandler(ProjectConfig *configManager,
				StateManager<WiFiState_e> *stateManager,
				const std::string &ssid,
				const std::string &password,
				uint8_t channel);
	virtual ~WiFiHandler();
	void setupWifi();

	ProjectConfig *configManager;
	StateManager<WiFiState_e> *stateManager;
	ProjectConfig::WiFiTxPower_t *txpower;

	bool _enable_adhoc;

private:
	void setUpADHOC();
	void adhoc(const char *ssid, const char *password, uint8_t channel);
	void iniSTA();

	std::string ssid;
	std::string password;
	uint8_t channel;
	uint8_t power;
};
#endif // WIFIHANDLER_HPP
