#ifndef CMMC_LEGEND_H
#define CMMC_LEGEND_H 

#include <Arduino.h> 
#include "version.h"
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <AsyncWebSocket.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <CMMC_ConfigManager.h>
#include "CMMC_System.hpp"
#include <vector>
#include "CMMC_Module.h"
#include <SPIFFSEditor.h> 


static AsyncWebServer server(80);
static AsyncWebSocket ws("/ws");
static AsyncEventSource events("/events");

enum MODE {SETUP, RUN};

class CMMC_Debugger {
  public: 
    CMMC_Debugger(Stream *s) { 
      if (_serial) {
        delete _serial;
        _serial = NULL; 
      }
      _serial = s;
    } 

    void println(char *s) {
      if (_serial) {
        _serial->println(s); 
      } 
    }
  Stream *_serial;
};

class CMMC_Legend: public CMMC_System {
  public:
    void addModule(CMMC_Module* module); 
    void run(); 
    void isLongPressed();
    void setup(); 
    void addDebugSerial(Stream *s);
  protected: 
    void init_gpio(); 
    void init_fs();
    void init_user_sensor(); 
    void init_user_config(); 
    void init_network(); 
    bool setEnable(bool status);

  private:
    MODE mode;
    std::vector<CMMC_Module*> _modules;
    char ap_ssid[30] = "CMMC-Legend";
    void _init_ap(); 
    void setupWebServer(AsyncWebServer *server, AsyncWebSocket *ws, AsyncEventSource *events); 
    bool stopFlag = false;
    CMMC_Debugger *debugger;
};

#endif