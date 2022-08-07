#if 0
#include <iostream>

namespace test_static {
    class Account {
    public:
        Account(int peroid = 9):peroid_1_(peroid){
            
        }
        static double rate(){
            return interest_rate_;
        }
        static double getPeroid_2_(){
            return peroid_2_;
        }
        
    private:
        static constexpr double interest_rate_ = 0.395;   // [RIGHT]静态常量表达式,只能在类内提供初始值
        // static const double interest_rate_ = 0.395;    // [ERROR]error: 'constexpr' needed for in-class initialization of static data member 'const double test_static::Account::interest_rate_' of non-integral type
        static int peroid_;
        const int peroid_1_;
        static const int peroid_2_ = 0;     // [+],static const类型的成员可在类内初始化或类外初始化，如果类内初始化了，类外可不再定义，但一般还是会在类外定义
    };
    
    int Account::peroid_ = 30;    // [RIGHT]
   
    constexpr double Account::interest_rate_;   // 此句可写、可不写,通常应该写；但此时不能再指定初始值了
    //const int Account::peroid_2_;          // [++],此句可写、可不写,通常应该写,如果类内初始化过了此处不可再赋值,如果类内没初始化此处需要初始化


    auto main() -> int {
        std::cout << "testing test_static......\n" << std::endl;

        Account acc;
        std::cout << acc.rate() << std::endl;
        std::cout << Account::rate() << std::endl;
        
        std::cout << Account::getPeroid_2_() << std::endl;
        
		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
#endif

#include <iostream>

namespace test_static {
    class Bar {
    public:
        Bar& clear(int i = bg);  // 静态成员和普通成员的区别1：静态成员可以作为默认实参
    private:
        static Bar mem1; /* 静态成员和普通成员的区别2：静态成员独立于任何对象,因此,在某些非静态数据成员可能非法的场合,静态成员却可以正常使用
                            例如本示例中,静态数据成员可以是不完全类型 */
        // Bar mem2;     // 错误,数据成员必须是完全类型
        
        static int bg;
    };


    auto main() -> int {
        std::cout << "testing test_static......\n" << std::endl;


		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
