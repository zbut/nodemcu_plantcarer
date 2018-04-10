//
//  limited_file.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 10/04/2018.
//
//

#include "limited_file.hpp"
#include "FS.h"

cLimitedFile::cLimitedFile(const char* file_name, const size_t max_size_in_bytes) : m_file_name(file_name), m_max_size_in_bytes(max_size_in_bytes), m_current_size_in_bytes(0)  {
    SPIFFS.begin();
    File log_file = SPIFFS.open(m_file_name, "w");
    if (log_file) {
        log_file.println("Starting limited file");
    }
    log_file.close();
}

cLimitedFile::~cLimitedFile() {}

int cLimitedFile::println(const char* line) {
    size_t bytes_to_add = strlen(line);
    if (bytes_to_add > m_max_size_in_bytes) {
        return 0;
    }
    check_size_and_empty_if_needed(bytes_to_add);
    File log_file = SPIFFS.open(m_file_name, "a");
    int ret_val = 0;
    if (log_file) {
        ret_val = log_file.println(line);
    }
    log_file.close();
    return ret_val;
}

void cLimitedFile::check_size_and_empty_if_needed(const size_t bytes_to_add) {
    // Check size after adding the given bytes
    if (m_current_size_in_bytes + bytes_to_add > m_max_size_in_bytes) {
        File log_file = SPIFFS.open(m_file_name, "w");
        if (log_file) {
            log_file.println("Restarting limited file");
        }
        log_file.close();
    }
}
