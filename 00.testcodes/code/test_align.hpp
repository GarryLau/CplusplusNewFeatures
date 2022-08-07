
#include <iostream>
#include <typeinfo>
#include <stdio.h>

namespace test_align {

    auto main() -> int {
        std::cout << "testing test_align......\n" << std::endl;

#if 0        
        unsigned char a = 0;
        std::cout << typeid(a).name() << std::endl;
        printf("&a = %p, sizeof(a) = %d\n", &a, sizeof(a));
        if(size_t(&a) % sizeof(a) == 0) {
            std::cout << "a's address starts with times of sizeof(a)." << std::endl;
        }
        std::cout << std::endl;
        
        short b = 0;
        std::cout << typeid(b).name() << std::endl;
        printf("&b = %p, sizeof(b) = %d\n", &b, sizeof(b));
        if(size_t(&b) % sizeof(b) == 0) {
            std::cout << "b's address starts with times of sizeof(b)." << std::endl;
        }
        std::cout << std::endl;

        int c = 0;
        std::cout << typeid(c).name() << std::endl;
        printf("&c = %p, sizeof(c) = %d\n", &c, sizeof(c));
        if(size_t(&c) % sizeof(c) == 0) {
            std::cout << "c's address starts with times of sizeof(c)." << std::endl;
        }
        std::cout << std::endl;

        long d = 0;
        std::cout << typeid(d).name() << std::endl;
        printf("&d = %p, sizeof(d) = %d\n", &d, sizeof(d));
        if(size_t(&d) % sizeof(d) == 0) {
            std::cout << "d's address starts with times of sizeof(d)." << std::endl;
        }
        std::cout << std::endl;

        long long e = 0;
        std::cout << typeid(e).name() << std::endl;
        printf("&e = %p, sizeof(e) = %d\n", &e, sizeof(e));
        if(size_t(&e) % sizeof(e) == 0) {
            std::cout << "e's address starts with times of sizeof(e)." << std::endl;
        }
        std::cout << std::endl;

        float f = 0;
        std::cout << typeid(f).name() << std::endl;
        printf("&f = %p, sizeof(f) = %d\n", &f, sizeof(f));
        if(size_t(&f) % sizeof(f) == 0) {
            std::cout << "f's address starts with times of sizeof(f)." << std::endl;
        }
        std::cout << std::endl;

        double g = 0;
        std::cout << typeid(g).name() << std::endl;
        printf("&g = %p, sizeof(g) = %d\n", &g, sizeof(g));
        if(size_t(&g) % sizeof(g) == 0) {
            std::cout << "g's address starts with times of sizeof(g)." << std::endl;
        }
        std::cout << std::endl;
#endif

#if 0
        typedef struct _ST_A_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stA;
        
        typedef struct _ST_C_
        {
           char c;
           stA sta;
        }stC;

        printf("sizeof double, int, char = %d, %d, %d\n", sizeof (double), sizeof (int), sizeof (char));
        printf("Sizeof stA = %d, stC = %d\n", sizeof(stA), sizeof(stC));
#endif

//  使用指令#pragma pack(n),C编译器将按照n个字节对齐;使用指令#pragma pack(),取消自定义字节对齐方式

/*
#pragma pack(n)用来设定变量以n字节对齐方式,变量存放的起始地址的偏移量：
1. 如果n大于等于该变量所占用的字节数，那么偏移量必须满足默认的对齐方式
2. 如果n小于该变量的类型所占用的字节数，那么偏移量为n的倍数，不用满足默认的对齐方式。
3. 结构的总大小也有一个约束条件,如果n大于等于所有成员变量类型所占用的字节数,那么结构的总大小必须为占用空间最大的变量占用的空间数的倍数;否则必须是n的倍数。
*/

#if 0
#pragma pack(1)
        typedef struct _ST_A_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stA;
#pragma pack()


#pragma pack(2)
        typedef struct _ST_B_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stB;
#pragma pack()


#pragma pack(3)   // [MinGW Makefiles] warning: alignment must be a small power of two, not 3 
                  // [Visual Studio 15 2017] warning C4086: 杂注参数应为“1”、“2”、“4”、“8”或者“16”
        typedef struct _ST_C_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stC;
#pragma pack()


#pragma pack(4)
        typedef struct _ST_D_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stD;
#pragma pack()


#pragma pack(8)
        typedef struct _ST_E_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stE;
#pragma pack()


#pragma pack(16)
        typedef struct _ST_F_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stF;
#pragma pack()


        typedef struct _ST_DEFAULT_
        {
           char c1;
           int i;
           char c2;
           double d;
        }stDefault;
        
        printf("sizeof stA = %d, stB = %d\n", sizeof(stA), sizeof(stB));
        printf("sizeof stC = %d, stD = %d\n", sizeof(stC), sizeof(stD));
        printf("sizeof stE = %d, stF = %d\n", sizeof(stE), sizeof(stF));
        printf("sizeof stDefault = %d\n", sizeof(stDefault));
#endif

#pragma pack(8)
        struct s1
        {
           short a;
           long b;
        };
        
        struct s2
        {
           char c;
            s1 d;
        long long e;
        };
        
        struct s3
        {
            char c;
            short a;
            long b;
            long long e;
        };
#pragma pack()

        printf("sizeof s1 = %d\n", sizeof(s1));
        printf("sizeof s2 = %d\n", sizeof(s2));
        printf("sizeof s3 = %d\n", sizeof(s3));

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
