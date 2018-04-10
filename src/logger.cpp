//
//  logger.cpp
//  nodemcu-plantcarer
//
//  Created by zbut on 24/12/2017.
//
//

#include "logger.hpp"
#include "serial.hpp"

cLogger logger_inst;

cLogger::cLogger() : m_serial() {

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

   // InfoUptime uptime;
   // get_uptime(&uptime);

   // the last zero will never get overwritten
   strncpy_P( m_format, (const char*)format_flash, MAX_LINE_LEN - 1);

   // int prefix_len = snprintf( buf , max_line_len, "[%02u:%02u:%02u] %c:",
   //                      uptime.hours, uptime.minutes, uptime.seconds, log_level_desc[to_integral(level)] );

   int prefix_len = snprintf( m_buffer , MAX_LINE_LEN, "%c:", log_level_desc[int(level)] );

   // fits or not, we have zeroed the whole thing so there will be ending zero.
   int print_len = vsnprintf( m_buffer + prefix_len,  MAX_LINE_LEN - prefix_len - 1, m_format, argument_list );

   int buffer_len = prefix_len + print_len;

   if (buffer_len >= MAX_LINE_LEN )
      buffer_len = MAX_LINE_LEN - 1;

   va_end( argument_list );
   m_serial.println(m_buffer);
}
