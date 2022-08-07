#pragma once

#include <new>
#include <cstdlib>
#include <iostream>

/*
    
    全局和类内都重载opeator new和operator delete

*/

/*索引1，单个元素，抛出异常版本，开始****************************************************************/
void* operator new(size_t size){
    std::cout << "global, index 1, \"void* operator new(size_t size)\" called.\n";
    if(void* mem = malloc(size)) {
        return mem;
    }
    else {
        throw std::bad_alloc();
    }
}
void operator delete(void* ptr) noexcept {
    std::cout << "global, index 1, \"void operator delete(void* ptr) noexcept\" called.\n";
    free(ptr);
}
/*单个元素，抛出异常版本，结束****************************************************************/

auto testGlobalOperatorNewDelete() -> int {
    std::cout << "testing global operator new & operator delete..." << std::endl;

    int *p1 = ::new int;
    // int *p1 = new int;  // 此句与上句一样都是调用重载版本的void* operator new(size_t size)
    ::delete p1;
    p1 = nullptr;
    std::cout << "++++++++++\n";
    
    std::cout << "------------------------------" << std::endl;
    return 0;
}
