#include "test_initializer_list.h"
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <complex>
#include <algorithm>   // std::max

namespace test_initializer_list
{
	auto myPrint(std::initializer_list<int> il) -> void
	{
		for(auto it: il){
			std::cout << it << ", ";
		}
		std::cout << std::endl;
	}
	
	auto hybridTest() -> void
	{
		int arr[]{1,2,3,4,5};
		for(auto it : arr)std::cout << it << ", ";std::cout << "sizeof arr is " << sizeof(arr)/sizeof(arr[0]) << std::endl;
		
		std::vector<std::string> vec{"visual", "studio", "Ninja", "MinGW Makefiles", "Unix Makefiles"};
		for(auto it : vec)std::cout << it << ", ";std::cout << std::endl;
		
		std::initializer_list<int> il1{3,4,5,6,7,8,9};
		std::initializer_list<int> il2({13,14,15,16,17,108});
		for(auto it : il1)std::cout << it << ", ";std::cout << std::endl;
		for(auto it : il2)std::cout << it << ", ";std::cout << std::endl;
		
		std::initializer_list<int> il3;
		std::cout << "sizeof il3: " << il3.size() << std::endl;
		
		std::complex<double> cpx{42.0, 23.1};
		std::cout << cpx.real() << "+" << cpx.imag() << "i" << std::endl;
		
		std::vector<int> v1{1,2,3,45};
		v1.insert(v1.begin()+2, {7,8,9});
		for(auto it : v1) std::cout << it << ", "; std::cout << std::endl;
		
		std::cout << std::max({std::string("Ace"), std::string("Stacy"), std::string("Ball"), std::string("Turkey")}) << std::endl;
	}
	
	// pass by value
	void func0val(std::initializer_list<std::string> lis){
        std::cout << "func0val(): " << std::endl;
        std::cout << "&lis = " << &lis << std::endl;
		for(auto it = lis.begin(); it != lis.end(); ++it)
		{
			std::cout << *it << ", " << &(*it) << std::endl;
		}
	}
	
	// pass by reference
	void func0ref(std::initializer_list<std::string>& lis){
        std::cout << "func0ref(): " << std::endl;
        std::cout << "&lis = " << &lis << std::endl;
		for(auto it = lis.begin(); it != lis.end(); ++it)
		{
			std::cout << *it << ", " << &(*it) << std::endl;
		}
	}
	
	void func1(std::initializer_list<std::string> const& lis){
		for(auto it = lis.begin(); it != lis.end(); ++it)
		{
			std::cout << *it << ", " << it << std::endl;
		}
	}

	void func2(std::initializer_list<std::string> &&lis){
		for(auto it = lis.begin(); it != lis.end(); ++it)
		{
			std::cout << *it << ", " << it << std::endl;
		}
	}
	
	auto valrefTest() -> void
	{
		std::string s1("Hello");
		std::string s2("Alice");
		std::string s3("Hi");
		std::string s4("CMake");
		
		// std::cout << s1 << ", " << &s1 << std::endl;
		// std::cout << s2 << ", " << &s2 << std::endl;
		// std::cout << s3 << ", " << &s3 << std::endl;
		// std::cout << s4 << ", " << &s4 << std::endl;
        
		std::initializer_list<std::string> li{s1, s2, s3, s4};
		for(auto it : li){  // range-based for,基于范围的for循环冒号“:”右侧必须是容器(提供begin/end方法)
			std::cout << it << ", " << &it << std::endl;
			/* 此处可能的输出：
			   Hello, 0x7ffd122ec840
               Alice, 0x7ffd122ec840
               Hi, 0x7ffd122ec840
               CMake, 0x7ffd122ec840
			   对的,输出的四个地址相同,因为基于范围的for是把元素拷贝进it,
			   其实输出的都是it这个临时变量的地址,不是li的元素的地址
			*/
		}
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        std::cout << "&li = " << &li << std::endl;
		for(auto it = li.begin(); it != li.end(); ++it)
		{
			std::cout << *it << ", " << &(*it) << " vs " << it << std::endl;
			/* 此处可能的输出：
			   Hello, 0x7ffd27680bf0
               Alice, 0x7ffd27680c10
               Hi, 0x7ffd27680c30
               CMake, 0x7ffd27680c50
			   输出的是每个元素的地址
			*/
		}
        func0val(li);
		func0ref(li);
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        
		std::cout << "A bunch of functions: " << std::endl;
		func0val(li);
		func0val({s1, s2, s3, s4});  // {s1, s2, s3, s4}会产生一个*没名字的*右值,右值的内容不可以被改动
		func0ref(li);
		// func0ref({s1, s2, s3, s4}); // [g++.exe (GCC) 11.2.0] error: cannot bind non-const lvalue reference of type 'std::initializer_list<std::__cxx11::basic_string<char> >&' to an rvalue of type 'std::initializer_list<std::__cxx11::basic_string<char> >'
		func1(li);
		func1({s1, s2, s3, s4});
		// func2(li);  // [g++.exe (GCC) 11.2.0] error: cannot bind rvalue reference of type 'std::initializer_list<std::__cxx11::basic_string<char> >&&' to lvalue of type 'std::initializer_list<std::__cxx11::basic_string<char> >'
		func2({s1, s2, s3, s4});
		std::cout << "*****************\n";
	}	
	
	auto main() -> int
	{
		std::cout << "testing initializer_list..." << std::endl;

		myPrint({-1, 1,2,3,90});

		hybridTest();
		
		valrefTest();		
		
		//Wiget awiget{1, 10.0};    // [ERROR & WARNING]编译器1."Visual Studio 15 2017 -A x64"的报错：
                     		      //       error C2398: 元素“2”: 从“double”转换到“bool”需要收缩转换;
                          		  //       warning C4305: “初始化”: 从“double”到“bool”截断
								  // [ERROR]编译器2. g++.exe (GCC) 11.2.0的报错：
								  //       error: narrowing conversion of '1.0e+1' from 'double' to 'bool' [-Wnarrowing]
								  // [RIGHT]编译器3. g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0可编译通过,可正常运行,运行结果为：Wiget(std::initializer_list<bool>) is called.
								  
		
		
		//Wiget bwiget{1, 10};      // [ERROR & WARNING]编译器1."Visual Studio 15 2017 -A x64"的报错[ERROR & WARNING]：
                                  //       error C2398: 元素“2”: 从“int”转换到“bool”需要收缩转换;
                                  //       warning C4305: “初始化”: 从“int”到“bool”截断
								  // [ERROR]编译器2. g++.exe (GCC) 11.2.0的报错：
								  //       error: narrowing conversion of '1.0e+1' from 'double' to 'bool' [-Wnarrowing]
								  // [ERROR]编译器3. g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0的报错：
								  //       error: narrowing conversion of ‘10’ from ‘int’ to ‘bool’ inside { } [-Wnarrowing]
								   
		
		Wiget cwiget{true, false};   // [RIGHT] Wiget(std::initializer_list<bool>) is called.
		Wiget dwiget(1, 10.0);       // [RIGHT] Wiget(int i, double j) is called.
		Wiget ewiget(1, 10);	     // [RIGHT] Wiget(int i, int j) is called.

		std::cout << "initializer_list test pass" << std::endl;
		std::cout << "------------------------------" << std::endl;

		return 0;
	}
}