//
//  limited_file.hpp
//  nodemcu-plantcarer
//
//  Created by zbut on 10/04/2018.
//
//

#ifndef limited_file_hpp
#define limited_file_hpp

#include "arduino.h"

class cLimitedFile {
public:
    cLimitedFile(const char* file_name, const size_t max_size_in_bytes);
    ~cLimitedFile();

    int println(const char* line);
protected:
    const char* m_file_name;
    const size_t m_max_size_in_bytes;
    size_t m_current_size_in_bytes;

    void check_size_and_empty_if_needed(const size_t bytes_to_add);
};


#endif /* limited_file_hpp */
