#if 0
#pragma once

#include <iostream>
#include <stdexcept>

namespace test_exception_function_try_blocks {
    class Element {
    public:
        Element(int val):val_(val){
            std::cout << "Element ctor called." << std::endl;
            throw std::runtime_error("Element ctor exception.");
        }
        virtual ~Element() = default;
    protected:
        int val_;
    };
    
    class Entity {
    public:
        Entity(int val);
        ~Entity() noexcept(true){
            std::cout << "Element dtor called.\n";
        }
        
    private:
        Element ele_;
    };

    Entity::Entity(int val) try : ele_(val){
        std::cout << "Entity ctor called.\n";
    }
    catch(const std::exception& e) {
        std::cout << "function-try-block caught: " << e.what() << std::endl;
        
        throw std::runtime_error("Exception occurs.");
    }
    
    auto main() -> int {
		std::cout << "testing exception_function_try_blocks..." << std::endl;

        try{
            Entity entity(3);    
        }
        catch(const std::exception& e) {
            std::cout << "main() caught: " << e.what() << std::endl;
        }
        
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}
#endif

#pragma once

#include <iostream>
#include <stdexcept>

namespace test_exception_function_try_blocks {
	class Foo {
	public:
		Foo(){
			std::cout << "Foo ctor called.\n";
		}
		virtual ~Foo(){
			std::cout << "Foo dtor called.\n";
		}		
	};

	class Bar {
	public:
		Bar(){
			std::cout << "Bar ctor called.\n";
		}
		virtual ~Bar(){
			std::cout << "Bar dtor called.\n";
		}		
	};
	
    class Element {
    public:
        Element(int val): foo_(), val_(val){
            std::cout << "Element ctor called." << std::endl;
            throw std::runtime_error("Element ctor exception.");
        }
        virtual ~Element() = default;
        int getVal() const noexcept{
            return val_;
        }
    protected:
        int val_;
		Foo foo_;
    };
    
    class Entity {
    public:
        Entity(int val);
        virtual ~Entity() noexcept(true){
            std::cout << "Entity dtor called.\n";
        }
        
    private:
		// ele_在bar_之前,因此先构造ele_,再构造bar_
        Element ele_;
		Bar bar_;
    };

    Entity::Entity(int val) try : bar_(), ele_(val){
        std::cout << "Entity ctor called.\n";
        //throw std::runtime_error("Entity ctor exception.");
    }
    catch(const std::exception& e) {
		std::cout << "Entering Entity's function-try-block......\n";
        std::cout << "function-try-block caught: " << e.what() << std::endl;
        // return;  // [ERROR]Visual Studio 15 2017, error C2176: 不能在与构造函数关联的函数 try 块的处理程序中使用 return 语句
                 //        MinGW Makefiles, error: cannot return from a handler of a function-try-block of a constructor
        throw std::runtime_error("Exception occurs.");
    }
    
    auto main() -> int {
		std::cout << "testing exception_function_try_blocks..." << std::endl;

        try{
            Entity entity(3);
        }
        catch(const std::exception& e) {
            std::cout << "main() caught: " << e.what() << std::endl;
        }
        
		std::cout << "------------------------------" << std::endl;

        return 0;
	}
}