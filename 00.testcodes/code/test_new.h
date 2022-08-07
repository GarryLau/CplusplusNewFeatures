#ifndef TEST_NEW_H_
#define TEST_NEW_H_

#include <iostream>

#define SOURCE_REF Source_reference{__FILE__, __LINE__}

namespace test_new
{
    struct Source_reference
    {
        char const* filename;
        int line_number;
    };
	
    extern const int bufSize;
    
	auto main() -> int;
}
#endif