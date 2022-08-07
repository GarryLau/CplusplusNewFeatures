#pragma once

#include <iostream>
#include <stdexcept>

namespace test_exception_ctor {
    class Element {
    public:
        Element(){
            std::cout << "Element ctor called, idx: " << count_++ << std::endl;
        }
        ~Element(){
            std::cout << "Element dtor called, idx: " << --count_ << std::endl;
        }        
    protected:
        int val_;
        static int count_;
    };
    
    int Element::count_ = 0;
    
    class Matrix {
    public:
        Matrix(int w, int h);
        ~Matrix() {
            std::cout << "Calling Matrix dtor." << std::endl;
            
            for(int i = 0; i < height_; ++i) {
                delete [] ele_[i];
            }
            delete [] ele_;
            ele_ = nullptr;
            
            std::cout << "Matrix dtor called." << std::endl;
        }
        
    private:
        int width_, height_;
        Element **ele_;
    };
    
    Matrix::Matrix(int w, int h): width_(w), height_(h), ele_(nullptr) {
        std::cout << "Calling Matrix ctor." << std::endl;
        
        ele_ = new Element*[height_];
        
        int i = 0;
        try {
            for(i = 0; i < height_; ++i) {
                std::cout << "i = " << i << std::endl;
                
                if(i == 2) throw std::bad_alloc();  // 此句模拟i==2时内存申请失败,抛出异常

                ele_[i] = new Element[width_];
            }
        }
        catch(...) {
            std::cerr << "exception occurs, idx: " << i << std::endl;
            
            // 释放已经申请的内存
            for(int j = 0; j < i; ++j) {
                delete[] ele_[j];
            }
            delete[] ele_;
            ele_ = nullptr;

            // Translate any exception to std::bad_alloc
            throw std::bad_alloc();
        }
        
        std::cout << "Matrix ctor called." << std::endl;
    }
    
    auto main() -> int {
		std::cout << "testing exception ctor..." << std::endl;

        try{
            Matrix amatrix(3,4);
        }
        catch(...) {
            std::cerr << "exception(s) occur(s)." << std::endl;
        }
        
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}

