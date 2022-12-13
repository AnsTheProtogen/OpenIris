#ifndef AutoDiscovery_hpp
#define AutoDiscovery_hpp

#include <ESPmDNS.h>
#include <WiFi.h>
#include "data/StateManager/StateManager.hpp"
#include "data/utilities/Observer.hpp"
#include "data/utilities/helpers.hpp"
#include "data/config/project_config.hpp"

class AutoDiscovery : public IObserver
{
private:
    StateManager<MDNSState_e> *stateManager;
    ProjectConfig *configManager;
    ProjectConfig::MDNSConfig_t *mdnsConfig;
    void (*callback)(const char *);

public:
    AutoDiscovery(StateManager<MDNSState_e> *stateManager,
                  ProjectConfig *configManager);
    ~AutoDiscovery();
    void start();
    int queryService(const std::string &service, const std::string &protocol);
    void stop();
    void setCallback(void (*callback)(const char *));
    void update(ObserverEvent::Event event);
};

#endif // AutoDiscovery_hpp