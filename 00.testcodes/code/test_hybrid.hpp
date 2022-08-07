#include <iostream>
#include <iterator>
#include <typeinfo>

/*
    编译环境：cmake -G "Visual Studio 15 2017" -A x64 ..
*/
namespace test_hybrid
{
	void testPointArray(){
		int a[2][3] = {-1,-2,-3,1,2,3};
		int (*p)[3] = a; // p是数组指针,每加1步进a的一个元素个大小,即3*sizeof(int);(注意多维数组是数组的数组,即a的每个元素是int[3])
		for(int i = 0; i < 3; ++i){
            // 可能的输出p[0] = 00000000001BF7C8, p[1] = 00000000001BF7D4, p[2] = 00000000001BF7E0,
			std::cout << "p[" << i << "] = " << p[i] << ", ";
		}
		std::cout << std::endl;
		
		// p = a[1];  // error C2440: “=”: 无法从“int [3]”转换为“int (*)[3]”
		p = &a[1];
		for(int i = 0; i < 3; ++i){
			std::cout << "(*p)[" << i << "] = " << (*p)[i] << ", ";
		}
		std::cout << std::endl;		
	}
	
	void testBeginEnd(){
		std::cout << "testBeginEnd()" << std::endl;
		int a[2][3] = {-1,-2,-3,1,2,3};
		
		auto itbegin = std::begin(a);  // 返回指向a的首元素的指针,即int(*)[3]
		auto itend = std::end(a);      // 返回指向a的尾元素下一位置的指针
		auto size = itend - itbegin;
		// 输出The size of array a is: 2, type(itbegin): int (*)[3]
        std::cout << "The size of array a is: " << size << ", type(itbegin): " << typeid(itbegin).name() << std::endl;
		
		for(auto it = itbegin; it != itend; ++it) {
			//std::cout << typeid(it).name() << ", ";   // int (* __ptr64)[3]
			for(auto it2 = 0; it2 < 3; ++it2) {
				std::cout << (*it)[it2] << ", ";
			}
		}
		std::cout << std::endl;

		//std::cout << typeid(std::begin(*itbegin)).name() << std::endl;   // int * __ptr64
		
		for(auto it = itbegin; it != itend; ++it) {
			for(auto it2 = std::begin(*it); it2 != std::end(*it); ++it2) {
				std::cout << *it2 << ", ";
			}
		}			
		std::cout << std::endl;		
	}

    void testFunc1(int(*p)[3], int size){
        std::cout << "&p is: " << &p << std::endl;            // 可能的输出: 0133F86C,与&a不同
        std::cout << "&(p[0]) is: " << &(p[0]) << std::endl;  // 可能的输出: 0133F880,与&a相同
        for(int i = 0; i < size; ++i){
            for(auto it: p[i]){
                std::cout << it << ", ";
            }
        }
        std::cout << std::endl;
    }
    
    void testFunc2(int **p){
        std::cout << "Entering testFunc2()...\n";
    }
	
	auto main() -> void {
		std::cout << "testing hybrid..." << std::endl;
		
	    testPointArray();
		
		//testBeginEnd();
        
        int a[2][3] = {-1,-2,-3,1,2,3};
        std::cout << "&a is: " << &a << std::endl;  // 可能的输出: 0133F880
        testFunc1(a, sizeof(a) / sizeof(a[0]));
        
        // testFunc2(a); // [ERROR]error: cannot convert 'int (*)[3]' to 'int**'
        
        auto b = a;
        std::cout << "type(b): " << typeid(b).name() << std::endl;  // int (* __ptr64)[3]
        
        int a2[] = {1,2,3,4};
        auto c = a2;
		std::cout << "type(c): " << typeid(c).name() << std::endl;  // int * __ptr64
        auto &d = a2;
        std::cout << "type(d): " << typeid(d).name() << std::endl;  // int [4]
        
		std::cout << "------------------------------" << std::endl;
	}
}
