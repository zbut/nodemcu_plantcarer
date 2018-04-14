//
//  logger.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 24/12/2017.
//
//

#ifndef logger_hpp
#define logger_hpp

#include "Arduino.h"
#include "serial.hpp"
#include "limited_file.hpp"

class cLogger {
public:
    enum class eLevel { DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3, FATAL = 4};
    cLogger();
    ~cLogger();

    void log( cLogger::eLevel level, const __FlashStringHelper* format, ... );
protected:
    static const int MAX_LINE_LEN = 80;
    const char* m_log_file_path = "/log.txt";

    char m_buffer[ MAX_LINE_LEN ];
    char m_format[ MAX_LINE_LEN ];
    cSerial m_serial;
    cLimitedFile m_log_file;

};

extern cLogger logger_inst;

#define LOG_INFO( format, ... ) logger_inst.log( cLogger::eLevel::INFO, F(format) , ## __VA_ARGS__ )
#define LOG_WARNING( format, ... ) logger_inst.log( cLogger::eLevel::WARNING, F(format), ## __VA_ARGS__ )
#define LOG_ERROR( format, ... ) logger_inst.log( cLogger::eLevel::ERROR, F(format), ## __VA_ARGS__ )
#define LOG_FATAL( format, ... ) logger_inst.log( cLogger::eLevel::FATAL, F(format), ## __VA_ARGS__ )

#endif /* logger_hpp */
