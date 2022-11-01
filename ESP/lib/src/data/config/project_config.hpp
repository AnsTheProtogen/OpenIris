#pragma once
#ifndef PROJECT_CONFIG_HPP
#define PROJECT_CONFIG_HPP
#include <Arduino.h>
#include <Preferences.h>
#include <vector>
#include <string>

#include "data/utilities/Observer.hpp"
#include "data/utilities/helpers.hpp"

class ProjectConfig : public Preferences, public ISubject
{
public:
	ProjectConfig(const std::string &name = std::string());
	virtual ~ProjectConfig();
	void load();
	void save();
	void wifiConfigSave();
	void cameraConfigSave();
	void deviceConfigSave();
	bool reset();
	void initConfig();

	struct DeviceConfig_t
	{
		std::string name;
		std::string OTAPassword;
		int OTAPort;

		std::string toRepresentation();
	};

	struct CameraConfig_t
	{
		uint8_t vflip;
		uint8_t href;
		uint8_t framesize;
		uint8_t quality;
		uint8_t brightness;

		std::string toRepresentation();
	};

	struct WiFiConfig_t
	{
		//! Constructor for WiFiConfig_t - allows us to use emplace_back
		WiFiConfig_t(const std::string &name,
					 const std::string &ssid,
					 const std::string &password,
					 uint8_t channel,
					 bool adhoc) : name(std::move(name)),
								   ssid(std::move(ssid)),
								   password(std::move(password)),
								   channel(channel),
								   adhoc(adhoc) {}
		std::string name;
		std::string ssid;
		std::string password;
		uint8_t channel;
		bool adhoc;

		const char *toRepresentation()
		{
			char *p = (char *)"wifi_entry: {";
			p += sprintf(p, "\"name\":%s,", this->name);
			p += sprintf(p, "\"ssid\":%s,", this->ssid);
			p += sprintf(p, "\"password\":%s,", this->password);
			p += sprintf(p, "\"channel\":%u,", this->channel);
			p += sprintf(p, "\"adhoc\":%u", this->adhoc);
			p += sprintf(p, "},");
			*p++ = 0;
			return p;
		}
	};

	struct AP_WiFiConfig_t
	{
		std::string ssid;
		std::string password;
		uint8_t channel;
		bool adhoc;
		const char *toRepresentation()
		{
			char *p = (char *)"adhoc_network: {";
			p += sprintf(p, "\"ssid\":%s,", this->ssid);
			p += sprintf(p, "\"password\":%s,", this->password);
			p += sprintf(p, "\"channel\":%u,", this->channel);
			p += sprintf(p, "\"adhoc\":%d", this->adhoc);
			p += sprintf(p, "},");
			*p++ = 0;
			return p;
		}
	};

	struct TrackerConfig_t
	{
		DeviceConfig_t device;
		CameraConfig_t camera;
		std::vector<WiFiConfig_t> networks;
		AP_WiFiConfig_t ap_network;
	};

	DeviceConfig_t *getDeviceConfig() { return &this->config.device; }
	CameraConfig_t *getCameraConfig() { return &this->config.camera; }
	std::vector<WiFiConfig_t> *getWifiConfigs() { return &this->config.networks; }
	AP_WiFiConfig_t *getAPWifiConfig() { return &this->config.ap_network; }

	void setDeviceConfig(const std::string &name, const std::string &OTAPassword, int *OTAPort, bool shouldNotify);
	void setCameraConfig(uint8_t *vflip, uint8_t *framesize, uint8_t *href, uint8_t *quality, uint8_t *brightness, bool shouldNotify);
	void setWifiConfig(const std::string &networkName, const std::string &ssid, const std::string &password, uint8_t *channel, bool adhoc, bool shouldNotify);
	void setAPWifiConfig(const std::string &ssid, const std::string &password, uint8_t *channel, bool adhoc, bool shouldNotify);

private:
	TrackerConfig_t config;
	bool _already_loaded;
	std::string _name;
};

#endif // PROJECT_CONFIG_HPP