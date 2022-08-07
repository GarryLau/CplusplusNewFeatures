#include <typeinfo>
#include <iostream>

namespace test_auto {
    auto testRangeForAuto() -> void {
        // 预备知识,数组引用
        int a[3][4] = {0,1,2,3};
        int (&arr_ref)[4] = a[2];
        for(auto &i : arr_ref){
            i = -99;
        }
        std::cout << "using array reference...\n";
        for(const auto &row : a){
            for(auto col : row){
                std::cout << col << std::endl;
            }
        }
        
        // 使用范围for语句处理多维数组，除了最内层的循环外，其它所有循环的控制变量都应该是引用类型
        std::cout << "Entering testRangeForAuto()...\n";
        for(auto &row : a){            // row是a每个元素(每个元素都是int[4])的引用
            for(auto &col : row){      // col是int类型
                col += 1;
            }
        }
        
        for(const auto &row : a){
            for(auto col : row){
                std::cout << col << std::endl;
            }
        }
        
        /*
        for(auto row : a){         // 这么写row会是int*,下面一行再对int*做range-for是不合适的
            for(auto col : row){}  // error: 'end' was not declared in this scope; did you mean 'std::end'?
        }
        */
    }
    
    auto main() -> int {
        std::cout << "testing auto......" << std::endl;

        int i = 19;
        const int ci = 18;

        // 基本类型,auto会忽略const
        auto a = i * i;
        auto b = ci;
        const auto c = ci;

        // auto得到引用时,会保留const
        auto &d = i;
        d = 10;          // [RIGHT]

        auto &e = ci;
        // e = 3;        //  error C3892: “e”: 不能给常量赋值

        // auto得到指针时,会保留const
        auto f = &i;
        auto g = &ci;
        // *g = 88;      // error C3892: “g”: 不能给常量赋值
        g = &i;          // [RIGHT],g是底层指针,可以指向不同变量但不能通过g修改所指向变量的值
        // *g = 78;      // error C3892: “g”: 不能给常量赋值


        // other test
        int * const q1 = &i;
        const int * const q2 = &i;
        int const * q3 = &i;  // q3和q4都是底层指针,两种写法相同
        const int * q4 = &i;

        std::cout << "type(a) is: " << typeid(a).name() << std::endl;   // int
        std::cout << "type(b) is: " << typeid(b).name() << std::endl;   // int
        std::cout << "type(c) is: " << typeid(c).name() << std::endl;   // int
        std::cout << "type(d) is: " << typeid(d).name() << std::endl;   // int
        std::cout << "type(e) is: " << typeid(e).name() << std::endl;   // int
        std::cout << "type(f) is: " << typeid(f).name() << std::endl;   // int *
        std::cout << "type(g) is: " << typeid(g).name() << std::endl;   // int const *

        std::cout << "type(q1) is: " << typeid(q1).name() << std::endl;   // 实际是int * const,编译器只写到int *
        std::cout << "type(q2) is: " << typeid(q2).name() << std::endl;   // 实际是int const * const,编译器只写到int const *
        std::cout << "type(q3) is: " << typeid(q3).name() << std::endl;   // int const *
        std::cout << "type(q4) is: " << typeid(q4).name() << std::endl;   // int const *

        // 对数组使用auto
        int arr[] = {3,4,5};
        auto brr(arr);    // auto数组得到的是指针,因此range-for中访问多维数组的时候需要对除最内层以外的所有层使用引用,详见testRangeForAuto()
        std::cout << "type(brr) is: " << typeid(brr).name() << std::endl;  // int *

        auto &ref_arr(arr);      // ref_arr是arr的引用
        std::cout << "type(ref_arr) is: " << typeid(ref_arr).name() << std::endl;  // int [3]
        ref_arr[1] = 888;
        std::cout << "arr[1] = " << arr[1] << std::endl;
        
        // decltype(arr) crr = {5,6,7,8,9};    //  error: too many initializers for 'int [3]'
        decltype(arr) drr = {5,6,7};           // 注意,数组元素的个数是数组类型的一部分
        std::cout << "type(drr) is: " << typeid(drr).name() << std::endl;   // int [3]

        testRangeForAuto();

		std::cout << "test_auto pass" << std::endl;
		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
