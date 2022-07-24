#pragma once
#include <Arduino.h>

#include "data/config/project_config.hpp"

class SerialManager
{
public:
    SerialManager();
    virtual ~SerialManager();

    void handleSerial();

    bool serialManagerActive;

    /* Device Config Variables */
    char device_config_name[32];
    char device_config_OTAPassword[100];
    int device_config_OTAPort;

    /* Camera Config Variables */
    uint8_t camera_config_vflip;
    uint8_t camera_config_framesize;
    uint8_t camera_config_href;
    uint8_t camera_config_quality;

    /* Wifi Config Variables */
    char wifi_config_name[32];
    char wifi_config_ssid[100];
    char wifi_config_password[100];

private:

    void listenToSerial(unsigned long timeout);
    void parseData();
    enum DataTypes_e
    {
        DataType_Unknown,
        DataType_Device,
        DataType_Camera,
        DataType_Wifi,
        DataType_Error,
        DataType_Debug
    };

    char serialBuffer[100000]; //! Need to find the appropriate size for this - count the maximum possible size of a message
    char tempBuffer[sizeof(serialBuffer) / sizeof(serialBuffer[0])];
    bool newData;
    
};

extern SerialManager serialManager;