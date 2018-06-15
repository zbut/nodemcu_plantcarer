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

   RtcDateTime time_struct = GET_TIME();

   // the last zero will never get overwritten
   strncpy_P( m_format, (const char*)format_flash, MAX_LINE_LEN - 1);

   snprintf( m_buffer , MAX_LINE_LEN, "[%02u:%02u:%02u]R %c:",
            time_struct.Hour(), time_struct.Minute(), time_struct.Second(), log_level_desc[int(level)] );

   va_end( argument_list );
   m_serial.println(m_buffer);
   m_log_file.println(m_buffer);
}
