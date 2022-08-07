#ifndef TEST_INITIALIZER_LIST_H_
#define TEST_INITIALIZER_LIST_H_

#include <iostream>
#include <initializer_list>


namespace test_initializer_list
{
	class Wiget{
	public:
		Wiget(int i, int j){std::cout << "Wiget(int i, int j) is called.\n";}
		Wiget(int i, double j){std::cout << "Wiget(int i, double j) is called.\n";}
		Wiget(std::initializer_list<std::string>){std::cout << "std::initializer_list<std::string>) is called.\n";}
		Wiget(std::initializer_list<bool>){std::cout << "Wiget(std::initializer_list<bool>) is called.\n";}
	};

	auto myPrint(std::initializer_list<int>) -> void;

	auto hybridTest() -> void;

	// pass by value
	void func0val(std::initializer_list<std::string> lis);	
	// pass by reference
	void func0ref(std::initializer_list<std::string>& lis);
    // pass by const reference	
	void func1(const std::initializer_list<std::string> &lis);
	// pass by right val reference
	void func2(std::initializer_list<std::string> &&lis);

	auto valrefTest() -> void;
	
	auto main() -> int;
}
#endif