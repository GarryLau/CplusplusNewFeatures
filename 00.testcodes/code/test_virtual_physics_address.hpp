
#include <stdlib.h>
#include <iostream>

namespace test_virtual_physics_address {

    auto main() -> int {
        std::cout << "testing test_virtual_physics_address......" << std::endl;

        int *p = (int *)malloc(1024*1024*1024);
        _sleep(3600000);

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
