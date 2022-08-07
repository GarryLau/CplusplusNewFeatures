#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

namespace test_exception1 {
	auto func2() -> void;
	auto func1() -> void {
	    std::string str1;
		
		std::string *str2 = new std::string();
		
		func2();
		
		delete str2;
	}

    auto func2() -> void {
		std::ifstream in_file("test.txt");
		
		throw std::exception();
		
		in_file.close();  // 此句虽然不会被执行但in_file会被正常关闭
	}
	
    auto main() -> int {
		std::cout << "testing exception..." << std::endl;
		
		try {
			func1();
		}
		catch(const std::exception& e) {
			std::cerr << "Line " << __LINE__ << ", " << e.what() << std::endl;
			return 1;
		}
		
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}

