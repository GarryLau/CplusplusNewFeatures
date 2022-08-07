#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

namespace test_exception2 {
	auto func() -> void {
		throw std::runtime_error("exception in func()");
	}
	
	auto testThrow1() -> void {
		std::ifstream in_file;
		try {
			std::string filename("testThrow.txt");
			in_file.open(filename);
			if(in_file.fail()) {  // 本示例假设文件打开成功,即不会走该if分支的异常
				throw std::runtime_error(filename.c_str());
			}
			func();
		}
		catch(const std::runtime_error& e) {
			std::cout << "Line " << __LINE__ << ", " << e.what() << std::endl;
		}
		catch(...) {
			std::cout << "Line " << __LINE__ << ", some exception occurs!" << std::endl;
		}
		
		// 异常发生时执行上面catch语句块,此句后面不会被执行,但因为in_file是局部变量,
		// 因此会调用ifstream析构函数,ifstream析构函数会自动关闭文件,因此不会泄漏资源
		// 如果in_file是动态分配的那么这个指针不会被销毁,文件也不会被关闭
        in_file.close();
	}

    auto testThrow2() -> void {
		int *p;
		
		try {
			p = new int;
			func();
		}
		catch(...) {
			std::cout << "Line " << __LINE__ << ", some exception occurs!" << std::endl;
		}
		
		// 异常发生时执行上面catch语句块,此句后面不会被执行,因此会产生内存泄漏
		delete p;
	}
	
    auto main() -> int {
		std::cout << "testing exception..." << std::endl;
		
		testThrow1();
		testThrow2();
		
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}
