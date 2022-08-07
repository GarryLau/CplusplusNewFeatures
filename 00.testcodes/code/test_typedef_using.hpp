#pragma once

#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

namespace test_typedef_using
{
    // typedef
    typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UptrMapSS;
    
    template <typename T>
    struct myAllocList1
    {
        typedef std::list<T, std::allocator<T>> listtype1;
    };
    
    class Foo{};
    
    template <typename T>
    class Wiget1
    {
    private:
        typename myAllocList1<T>::listtype1 list_;
    };
    
    // using
    using UptrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

    template <typename T>
    using myAllocList2 = std::list<T, std::allocator<T>>;
    
    template <typename T>
    class Wiget2
    {
    private:
        myAllocList2<T> list_;
    };
    
    
    int main()
    {
        std::cout << "test_typedef_using......." << std::endl;
        
        myAllocList1<int>::listtype1 alist1;
        Wiget1<Foo> blist1;
        
        myAllocList2<int> alist2;
        Wiget2<Foo> blist2;

        std::cout << "typedef_using pass,----------------------------" << std::endl;

        return 0;
    }
}
