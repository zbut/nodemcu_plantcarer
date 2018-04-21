//
//  logger.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 24/12/2017.
//
//

#include "logger.hpp"
#include "serial.hpp"
#include "rtc_w_ntp.hpp"
#include "FS.h"

cLogger logger_inst;

cLogger::cLogger() : m_serial(), m_log_file("/log_file.txt", 2000) {

}
cLogger::~cLogger() {}

void cLogger::log( cLogger::eLevel level,  const __FlashStringHelper* format_flash, ... )
{
   va_list argument_list;
   va_start ( argument_list, format_flash );

   memset(m_buffer, 0x00, MAX_LINE_LEN );
   memset(m_format, 0x00, MAX_LINE_LEN );
   // make the level visible
   const char log_level_desc[] = { 'D','I','W','E', 'F' };

   sTime time_struct;
   GET_TIME(&time_struct);

   // the last zero will never get overwritten
   strncpy_P( m_format, (const char*)format_flash, MAX_LINE_LEN - 1);

   int prefix_len;
   if (time_struct.is_up_time) {
       prefix_len = snprintf( m_buffer , MAX_LINE_LEN, "[%04u:%02u:%02u]U %c:",
                        time_struct.hours, time_struct.minutes, time_struct.seconds, log_level_desc[int(level)] );
   }
   else {
       prefix_len = snprintf( m_buffer , MAX_LINE_LEN, "[%02u:%02u:%02u]R %c:",
                        time_struct.hours, time_struct.minutes, time_struct.seconds, log_level_desc[int(level)] );
   }
   // fits or not, we have zeroed the whole thing so there will be ending zero.
   int print_len = vsnprintf( m_buffer + prefix_len,  MAX_LINE_LEN - prefix_len - 1, m_format, argument_list );

   va_end( argument_list );
   m_serial.println(m_buffer);
   m_log_file.println(m_buffer);
}
