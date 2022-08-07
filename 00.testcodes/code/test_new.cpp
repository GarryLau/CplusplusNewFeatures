#include "test_new.h"


// Note: while this example works nicely, it doesn't support threading.
#include <iostream>
#include <new>          // std::bad_alloc
#include <stddef.h>     // ptrdiff_t, size_t, max_align_t
#include <stdlib.h>     // malloc, EXIT_*,
#include <vector>


namespace test_new
{
    const int bufSize = 456;
    
    auto main() -> int
    {
        std::cout << "testing test_new......" << std::endl;



		std::cout << "test_new test pass" << std::endl;
		std::cout << "------------------------------" << std::endl;
        
        return 0;
    }
}
