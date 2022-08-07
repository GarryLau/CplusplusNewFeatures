#ifndef TEST_DISTINGUISH_PARENTHESES_BRACES_H_
#define TEST_DISTINGUISH_PARENTHESES_BRACES_H_

#include <iostream>
#include <atomic> 
#if 0
#include <utility>      // std::forward
#include <vector>
#include <list>
#include <deque>
#include <forward_list>

namespace test_distinguish_parentheses_braces
{
	template<typename T,         // type of object to create
             typename... Args>   // types of arguments to use
    void doSomeWorkParentheses(const T& obj, Args&&... args) {
        T localObject(std::forward<Args>(args)...);
        
        std::cout << "Parentheses, localObject size = " << localObject.size() << std::endl;
    }

    template<typename T,         // type of object to create
             typename... Args>   // types of arguments to use
        void doSomeWorkBraces(const T& obj, Args&&... args) {
            T localObject{std::forward<Args>(args)...};
            
            std::cout << "Braces, localObject size = " << localObject.size() << std::endl;
        }

	auto main() -> void {
		std::cout << "testing test_distinguish_parentheses_braces..." << std::endl;
        
        std::vector<int> vec;
        std::list<int> lst;
        std::deque<int> dq;
        std::forward_list<int> flst;
        
        doSomeWorkParentheses(vec, 10, 20);
        doSomeWorkBraces(vec, 10, 20);
        
        doSomeWorkParentheses(lst, 10, 20);
        doSomeWorkBraces(lst, 10, 20);

        doSomeWorkParentheses(dq, 10, 20);
        doSomeWorkBraces(dq, 10, 20);

        // std::forward_list<>无size()方法,可通过打印所有数据查看
        // doSomeWorkParentheses(flst, 10, 20);
        // doSomeWorkBraces(flst, 10, 20);

		std::cout << "------------------------------" << std::endl;
    }
}
#endif

namespace test_distinguish_parentheses_braces
{
    /* 2.可以使用{}、=，但不能使用()的情形 */
    class Widget {
    private:
        int x{0};    // fine, x's default value is 0
        int y = 0;   // also fine
        // int z(0);    // error: expected identifier before numeric constant; error: expected ',' or '...' before numeric constant
    };

	auto main() -> void {
		std::cout << "testing test_distinguish_parentheses_braces..." << std::endl;
        
        /* 1.可以使用{}()=,初始化的三种方式 */
        int x(0);    // initializer is in parentheses
        int y = 0;   // initializer follows "="
        int z{0};    // initializer is in braces, equals int z = {0};
    
        /* 3.可以使用{}、()，但不能使用=的情形, but it depends */
        std::atomic<int> ai{0};
        std::atomic<int> bi(0);
        //std::atomic<int> ci = 0; // 跟编译器、C++标准有关系
                                 // MinGW Makefiles, 自C++17以来的标准可编译通过
                                 // Visual Studio 15 2017自C++11以来的标准都可编译通过
                                 // MinGW Makefiles,C++14的报错是: error: use of deleted function 'std::atomic<int>::atomic(const std::atomic<int>&)'


        double a = 1.0, b = 2.0, c = 3.0;
        int sum1{a + b + c};    // warning: narrowing conversion of '((a + b) + c)' from 'double' to 'int' [-Wnarrowing]
        int sum2(a + b + c);
        int sum3 = a + b + c;
        
		std::cout << "------------------------------" << std::endl;
    }
}
#endif


