#include <typeinfo>
#include <iostream>

namespace test_decltype {
	double onlyDeclartionFunc();

    auto main() -> int {
		std::cout << "testing decltype..." << std::endl;
		
		/* 表达式是函数 */
		decltype(onlyDeclartionFunc()) sum = 34;   // 使用decltype根据函数类型推断类型时可以仅要求函数有声明，不要求函数有定义
		std::cout << "type(sum) is: " << typeid(sum).name() << std::endl;  // double
		
		/***************************************************************************/

		float i = 3.4f;
		decltype(i) a = 52;
		std::cout << "type(a) is: " << typeid(a).name() << std::endl;     // float
		
		// 使用decltype时会返回变量的真实类型(包括const和引用)，这与auto有区别
		const int ci = 0;        // const int
		const int &cj = ci;      // const int &
		decltype(ci) b = 9;      // const int
		// b = 10;   // error C3892: “b”: 不能给常量赋值
		decltype(cj) c = b;      // const int &
		// c = ci;   // error C3892: “c”: 不能给常量赋值
		decltype(cj) d = 9;     // const int &
		// decltype(cj) e;  // error C2530: “e”: 必须初始化引用
		std::cout << "type(ci) is: " << typeid(ci).name() << std::endl;  // const int（ps:编译器输出时不会带const，下同）
		std::cout << "type(cj) is: " << typeid(cj).name() << std::endl;  // const int &
		std::cout << "type(b) is: " << typeid(b).name() << std::endl;    // const int
		std::cout << "type(c) is: " << typeid(c).name() << std::endl;    // const int &
		std::cout << "type(d) is: " << typeid(d).name() << std::endl;    // const int &
		
		/***************************************************************************/
		
		// decltype(表达式)推断出引用类型的几种情况:
		// 1. 表达式本身是引用;
		// 2. 表达式是指针的解引用;
		// 3. 表达式加括号;
		int j = 0;
		int &k = j;
		int *p = &j;
		
		std::cout << "Original j, 0 == " << j << std::endl;
		
		decltype(k) f = k;     // f是j的引用(表达式本身是引用)
		f = 1;
		std::cout << "f is j's reference, 1 == " << j << std::endl;
		
		decltype(*p) g = j;    // g是j的引用(表达式是指针的解引用)
		g = 2;
		std::cout << "g is j's reference, 2 == " << j << std::endl;
		
		decltype((j)) h = j;   // h是j的引用(表达式加括号)
		h = 3;
		std::cout << "h is j's reference, 3 == " << j << std::endl;
		
		decltype(k+0) m = k;   // m是int,不是int&,因为k+0是int类型
		m = 4;
		std::cout << "m is not j's reference, 4 != " << j << std::endl;
        
        // 对数组使用decltype**得到的是数组类型
        int arr[] = {3,4,5};
        // decltype(arr) crr = {5,6,7,8,9};    //  error: too many initializers for 'int [3]'
        decltype(arr) drr = {5,6,7};           // 注意,数组元素的个数是数组类型的一部分
        std::cout << "type(drr) is: " << typeid(drr).name() << std::endl;   // int [3]
		
		/***************************************************************************/
		
		std::cout << "------------------------------" << std::endl;
        return 0;
    }
}