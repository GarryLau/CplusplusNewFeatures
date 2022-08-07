#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <stdio.h>

namespace test_exception_errorprocess {
    auto generalNew() -> void {
        double *p = nullptr;
        try {
            p = new double[10LL*1024*1024*1024];
            printf("generalNew(), p = %p\n", p);
        }
        catch(std::bad_alloc& e) {
            std::cerr << "generalNew(), Fail to allocate memory." << e.what() << std::endl;
        }
        delete [] p;
    }
	
    auto cStyleNew() -> void {
        double *p = nullptr;
        p = new(std::nothrow)double[10LL*1024*1024*1024];
        if(nullptr == p) {
            std::cerr << "cStyleNew(), Fail to allocate memory." << std::endl;
        }
        else {
            printf("cStyleNew(), p = %p\n", p);
        }
        delete[]p;
    }
    
    auto testThrow() -> void {
        int a = 10, b = 0;
        try {
            if(0 == b) {
                throw std::runtime_error("divided 0");
            }
            else{
                int c = a / b;        
            }
        }
        catch(std::runtime_error& e){
            std::cerr << "exception occurs: " << e.what() << std::endl;
        }
    }
    
    auto testWantThrow() -> void {
        int a = 10, b = 0;
        try {
            int c = a / b;        
        }
        catch(...){
            std::cerr << "exception occurs." << std::endl;
        }
    }    
    
    auto main() -> int {
		std::cout << "testing exception_errorprocess..." << std::endl;

        generalNew();
        cStyleNew();
        testThrow();
        testWantThrow();
        
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}

