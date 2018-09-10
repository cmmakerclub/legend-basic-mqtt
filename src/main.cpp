
#include <CMMC_Legend.h>

#include "modules/WiFiModule.h"
#include "modules/MqttModule.h"
#include "modules/ConfigButtonModule.h"

const char* MEOBOT_VERSION = "1.4";

CMMC_Legend *os; 

WiFiModule* wifiModule; 
MqttModule *mqttModule;

void setup()
{ 
  Serial.begin(115200); 

  os = new CMMC_Legend();
  // os->addDebugSerial(&Serial); 

  wifiModule = new WiFiModule(); 
  mqttModule = new MqttModule(); 

  os->addModule(wifiModule); 
  os->addModule(mqttModule); 

  os->setup();
  Serial.printf("APP VERSION: %s\r\n", LEGEND_APP_VERSION); 
} 

void loop()
{
  os->run();
}