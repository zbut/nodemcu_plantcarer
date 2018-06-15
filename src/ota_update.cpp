//
//  ota_update.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 15/06/2018.
//
//

#include "ota_update.hpp"
#include <ArduinoOTA.h>
#include "logger.hpp"
#include "config.hpp"
#include "status.hpp"
#include "FS.h"

cOtaUpdate::cOtaUpdate()  {}
cOtaUpdate::~cOtaUpdate() {}

void cOtaUpdate::setup() {
  ArduinoOTA.setHostname( CONFIG.ota.ota_hostname );

  ArduinoOTA.setPassword( CONFIG.ota.ota_password );

  ArduinoOTA.onStart([]()
  {
    LOG_WARNING("Update start!");
    SPIFFS.end();
    status_set_ota_in_progress(true);
  });

  ArduinoOTA.onEnd([]()
  {
    LOG_WARNING("Update done!");
    status_set_ota_in_progress(false);
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
  {
    static unsigned int last = 0xFF;
    unsigned int prog = (progress / (total / 100));

    if ( prog == last )
       return;

    last = prog;
    LOG_INFO("Progress: %u%%", prog );
  });

  ArduinoOTA.onError([](ota_error_t error) {
    status_set_ota_in_progress(false);
    LOG_FATAL("Error %u during update: ", error);
  });
  ArduinoOTA.begin();
}

void cOtaUpdate::loop() {
  ArduinoOTA.handle();
}
