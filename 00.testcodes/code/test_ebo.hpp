
#include <iostream>
#include <typeinfo>
#include <stdio.h>

namespace test_ebo {
    class Empty{};
    class Empty2{};

    class Derived1 : public Empty {
        
    };
    
    class Derived2 : public Empty {
    private:
        char c_;
    };
    
    class Derived3 : public Empty {
    private:
        int i_;
    };
    
    class MultipleDerived : public Derived1 {
        
    };

    class DerivedMultiBase : public Empty, public Empty2 {
        
    };    

    auto main() -> int {
        std::cout << "testing test_ebo......\n" << std::endl;

        std::cout << "sizeof(Empty): " << sizeof(Empty) << std::endl;         // 1
        std::cout << "sizeof(Derived1): " << sizeof(Derived1) << std::endl;   // 1
        std::cout << "sizeof(Derived2): " << sizeof(Derived2) << std::endl;   // 1
        std::cout << "sizeof(Derived3): " << sizeof(Derived3) << std::endl;   // 4
        std::cout << "sizeof(MultipleDerived): " << sizeof(MultipleDerived) << std::endl;     // 1
        std::cout << "sizeof(DerivedMultiBase): " << sizeof(DerivedMultiBase) << std::endl;   // 1
        std::cout << typeid(MultipleDerived).name() << std::endl;
        std::cout << typeid(DerivedMultiBase).name() << std::endl;

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
