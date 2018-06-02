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
            .ssid = "None",
            .password = "",
            .connection_timout_sec = 10,
        },

        .pump_times = {
            .active_time_of_day_start = {.day = 0, .hour = 5, .minute = 0, .second = 0},
            .active_time_of_day_end = {.day = 0, .hour = 14, .minute = 0, .second = 0},
            .pump_off_period = {.day = 0, .hour = 7, .minute = 0, .second = 0},
            .pump_on_period = {.day = 0, .hour = 0, .minute = 5, .second = 0},

        },

        .water_level = {.tank_hight_cm = 32},
};
