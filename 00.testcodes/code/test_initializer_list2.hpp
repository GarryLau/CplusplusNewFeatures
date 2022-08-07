#ifndef TEST_INITIALIZER_LIST2_H_
#define TEST_INITIALIZER_LIST2_H_

#include <iostream>

namespace test_initializer_list2
{
	class Wiget{
	public:
        Wiget(){std::cout << "Wiget default ctor is called.\n";}
		Wiget(int i, int j){std::cout << "Wiget(int i, int j) is called.\n";}
		Wiget(int i, double j){std::cout << "Wiget(int i, double j) is called.\n";}
        Wiget(std::initializer_list<float>){std::cout << "std::initializer_list<float>) is called.\n";}
        
        Wiget(const Wiget&){
            std::cout << "Wiget copy ctor is called.\n";
        }
        
        operator float() const {
            std::cout << "convert to float\n";
            return 1.0;
        }
	};

	auto main() -> void {
		std::cout << "testing test_initializer_list2..." << std::endl;
        
        Wiget a;      // call Wiget()
        // Wiget b();    // function declaration
        Wiget c{};    // call Wiget()
        Wiget d({});  // call Wiget(std::initializer_list<float>)
        Wiget e{{}};  // call Wiget(std::initializer_list<float>)
        std::cout << "===\n";
        
        Wiget f(a);   // call Wiget()
        std::cout << "===\n";
        Wiget g{a};   // call Wiget(std::initializer_list<float>)

		std::cout << "------------------------------" << std::endl;
    }
}
#endif
