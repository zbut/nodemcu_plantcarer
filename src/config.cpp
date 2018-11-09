//
//  config.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 21/04/2018.
//
//

#include "config.hpp"

const sConfig CONFIG = {
        .wifi = {
            .ssid = "xxxx",
            .password = "xxxx",
            .connection_timout_sec = 10,
        },

        .pump_times = {
            .active_time_of_day_start = {.day = 0, .hour = 5, .minute = 0, .second = 0},
            .active_time_of_day_end = {.day = 0, .hour = 6, .minute = 0, .second = 0},
            .pump_off_period = {.day = 0, .hour = 1, .minute = 0, .second = 0},
            .pump_on_period = {.day = 0, .hour = 0, .minute = 7, .second = 0},

        },

        .water_level = {.tank_hight_cm = 32},

        .ota = {
          .ota_hostname = "plantcarer",
          .ota_password = "xxx"
        },

        .thingspeak = {
          .host = "api.thingspeak.com",
          .api_key = "APIKEYHERE"
        }
};
