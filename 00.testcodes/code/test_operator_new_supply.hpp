
#pragma once

#include <new>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

static const int kSignature = 0xDEADBEEF;

void* operator new(size_t size) {
    if(void* mem = malloc(size + 2 * sizeof(int))) {
        *((int*)mem) = kSignature;
        *((int*)((unsigned char*)mem + sizeof(int) + sizeof(unsigned char)*size)) = kSignature;
        
        std::cout << "malloc successfully" << std::endl;
        return (unsigned char*)mem + sizeof(int);
    }
    else {
        throw std::bad_alloc();
    }
}

void operator delete(void *mem) noexcept {
    std::cout << "Entering self-define operator delete...\n";
    if(mem) {
        /* 注意,正常情况下operator delete里没法校验overuns,因为不知道内存大小就没法加偏移量
           也许你会说加一个额外参数,例如,void operator delete(void *mem, int extra) noexcept
           但这种形式只有在构造函数发生异常时才会调用 */
        // 当然有其它方法校验overuns,比如在delete时根据申请内存的大小进行偏移进行主动校验
        if((*(int*)((unsigned char*)mem - sizeof(int)) == kSignature)) {
            free((unsigned char*)mem - sizeof(int));
            std::cout << "free successfully" << std::endl;
        }
        else{
            std::cerr << "memory underruns!!!" << std::endl;
        }
    }
}
    
auto test_operator_new_main() -> void {
    std::cout << "testing operator new & operator delete for overruns&underruns..." << std::endl;

    int *ptr = new int;
    *((unsigned char*)ptr - 2) = 'P';
    
    delete ptr;
    
    std::cout << "------------------------------" << std::endl;
}
