#if 0
#include <typeinfo>
#include <iostream>
#include <string>
#include <new>
#include <stdio.h>

namespace test_operator_new {
	class MyMemory {
	public:
		MyMemory() try : pstr_(new std::string){    // 使用标准库的new
			std::cout << "MyMemory ctor called.\n";
		}
		catch(std::bad_alloc& e) {
			std::cerr << "bad_alloc caught in MyMemory's ctor, " << e.what() << std::endl;
			throw /*std::bad_alloc()*/;
		}
		virtual ~MyMemory() {
			delete pstr_;       // 使用标准库的delete
			pstr_ = nullptr;
			
			std::cout << "MyMemory dtor called.\n";
		}
		
		void reset() {
			std::cout << "reseting...\n";
			delete pstr_;                                // 使用标准库的delete
			pstr_ = new std::string("The reset one.");   // 使用标准库的new
			std::cout << "reset done.\n";
		}
		
		void print() {
			if(pstr_) std::cout << *pstr_ << std::endl;
		}

		/* self-define operator new & operator delete, 这些函数不管加不加关键字static都默认都是static */
		/*static*/ void* operator new(size_t size) {
			std::cout << "in-class self-define operator new called.\n";
			
			return ::operator new(size);
		}
		/*static*/ void operator delete(void* ptr) noexcept{
			std::cout << "in-class self-define operator delete called.\n";

			::operator delete(ptr);
		}
		/*static*/ void* operator new[](size_t size) {
			std::cout << "in-class self-define operator new[] called.\n";
			
			return ::operator new[](size);
		}
		/*static*/ void operator delete[](void* ptr) noexcept{
			std::cout << "in-class self-define operator delete[] called.\n";

			::operator delete[](ptr);
		}

		
		/*static*/ void* operator new(size_t size, const std::nothrow_t&) noexcept{
			std::cout << "in-class self-define noexcept version operator new called.\n";
			
			return ::operator new(size, std::nothrow);
		}
		/*static*/ void operator delete(void* ptr, const std::nothrow_t&) noexcept{
			std::cout << "in-class self-define noexcept version operator delete called.\n";
			
			::operator delete(ptr, std::nothrow);
		}
		/*static*/ void* operator new[](size_t size, const std::nothrow_t&) noexcept{
			std::cout << "in-class self-define noexcept version operator new[] called.\n";
			
			return ::operator new[](size, std::nothrow);
		}
		/*static*/ void operator delete[](void* ptr, const std::nothrow_t&) noexcept{
			std::cout << "in-class self-define noexcept version operator delete[] called.\n";
			
			::operator delete[](ptr, std::nothrow);
		}
       
#if 0
        void* operator new(size_t size, int extra) {
            std::cout << "in-class self-define operator new(size_t size, int extra)\n";
            
            return ::operator new(size);
        }
        void operator delete(void *ptr, int extra) noexcept{
            std::cout << "in-class self-define operator delete(void *ptr, int extra)\n";
            
            ::operator delete(ptr);
        }
#endif

	protected:
		std::string *pstr_;
	};
	
	
    auto main() -> int {
		std::cout << "testing operator new & operator delete..." << std::endl;

		MyMemory mymem;
		std::cout << "+++++\n";
		
		MyMemory *pmymem1 = ::new MyMemory();   // 使用标准库的new
		::delete pmymem1;                       // 使用标准库的delete
		//delete pmymem1;                       // 使用in-class self-define delete,
		                                        // 运行时不会因为new的时候使用的是标准库的new来自动找对应标准库的delete,
												// 想使用哪个版本的new和delete都必须要手动指定,但最好一一对应,即要么都使用标准库的版本要么都使用自定义版本
		std::cout << "+++++\n";
		
		MyMemory *pmymem2 = new MyMemory();     // 使用in-class self-define new
		pmymem2->reset();
		pmymem2->print();		
		delete pmymem2;                         // 使用in-class self-define delete
		
		std::cout << "+++++\n";
        MyMemory *pmymem3 = new(std::nothrow) MyMemory[3];
        delete [] pmymem3;


		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
#endif

#if 0
#include <iostream>
#include <new>

namespace test_operator_new {
	class MyMemory {
	public:
		MyMemory()=default;
		virtual ~MyMemory() {}
		
        void* operator new(size_t size) = delete;
        void* operator new[](size_t size) = delete;
	};
	
	
    auto main() -> int {
		std::cout << "testing operator new & operator delete..." << std::endl;

        MyMemory *p1 = new MyMemory;    // error: use of deleted function 'static void* test_operator_new::MyMemory::operator new(size_t)'
        MyMemory *p2 = new MyMemory[3]; // error: use of deleted function 'static void* test_operator_new::MyMemory::operator new [](size_t)'

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
#endif

#if 0   // 一会再试
#include <iostream>
#include <string>
#include <new>
#include <cstdlib>

namespace test_operator_new {
	class MyMemory {
	public:
		MyMemory() try : pstr_(new std::string("Default value.")){    // 使用标准库的new
			std::cout << "MyMemory ctor called.\n";
            //throw std::runtime_error("ddd");
		}
		catch(std::bad_alloc& e) {
			std::cerr << "bad_alloc caught in MyMemory's ctor, " << e.what() << std::endl;
			throw std::bad_alloc();
		}
		virtual ~MyMemory() {
			delete pstr_;       // 使用标准库的delete
			pstr_ = nullptr;
			
			std::cout << "MyMemory dtor called.\n";
		}
		
		void reset() {
			std::cout << "reseting...\n";
			delete pstr_;                                // 使用标准库的delete
			pstr_ = new std::string("The reset one.");   // 使用标准库的new
			std::cout << "reset done.\n";
		}
		
		void print() {
			if(pstr_) std::cout << *pstr_ << std::endl;
		}

        void* operator new(size_t size, int extra) {
			std::cout << "in-class self-define operator new (using malloc) called. size is: " << size << std::endl;
			if(void *mem = malloc(size)) {
                return mem;
            }
            else{
                throw std::bad_alloc();
            }
        }
        void operator delete(void *mem, int extra) noexcept {
			std::cout << "in-class self-define operator delete (using free) called.\n";

			free(mem);
        }

        /*void operator delete(void *mem) noexcept {
			std::cout << "operator delete(void *mem) called.\n";

			free(mem);
        }*/
        
        void* operator new(size_t size, const std::string& debug_info) {
			std::cout << "The following is new debug infomation: " << debug_info << ", size is: " << size << std::endl;
			if(void *mem = malloc(size)) {
                return mem;
            }
            else {
                throw std::bad_alloc();
            }
        }
        void operator delete(void *mem, const std::string& debug_info) noexcept{
			std::cout << "The following is delete debug infomation: " << debug_info << std::endl;

			free(mem);
        }

	protected:
		std::string *pstr_;
	};
	
	
    auto main() -> int {
		std::cout << "testing operator new & operator delete..." << std::endl;

        try {
            MyMemory *pmem = new MyMemory();
            std::cout << "sizeof(pmem): " << sizeof(pmem) << std::endl;
            pmem->print();
            delete pmem;
            pmem = nullptr;            
        }
        catch(...){
            std::cout << "Caught it." << std::endl;
            return 1;
        }

        MyMemory *pmem1 = new(std::string("Pyramid")) MyMemory();
        std::cout << "sizeof(pmem1): " << sizeof(pmem1) << std::endl;
        pmem1->print();
        delete pmem1;
        //MyMemory::operator delete(pmem1,std::string("Pyramid"));   // 这么做虽然调用了void operator delete(void *mem, const std::string& debug_info) noexcept的版本,但在内存释放之前的析构函数自动调用却没有了
        pmem1 = nullptr;

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
#endif

#pragma once

#include <new>
#include <cstdlib>
#include <iostream>
#include "test_global_operator_new.hpp"

/*
    
    如果在全局层次重载opeator new和operator delete那么标准库的版本会被隐藏；
    如果全局层次和类内都重载opeator new和operator delete时，对于类类型对象的new和delete会使用类内版本，对于其它对象会使用全局层次重载的operator new和operator delete；
    当对类类型对象使用全局作用域符::时得到的是全局层次的operator new和operator delete，不是标准库版本的

*/

namespace test_operator_new {
    class MyMemory {
    public:
        MyMemory() {
            std::cout << "MyMemory ctor called." << std::endl;
        }

        virtual ~MyMemory(){
            std::cout << "MyMemory dtor called." << std::endl;
        }

        /*索引1，单个元素，抛出异常版本，开始****************************************************************/
        void* operator new(size_t size){
            std::cout << "index 1, \"void* operator new(size_t size)\" called.\n";
            if(void* mem = malloc(size)) {
                return mem;
            }
            else {
                throw std::bad_alloc();
            }
        }
        void operator delete(void* ptr) noexcept {
            std::cout << "index 1, \"void operator delete(void* ptr) noexcept\" called.\n";
            free(ptr);
        }
        /*单个元素，抛出异常版本，结束****************************************************************/
    };
    
    auto main() -> int {
		std::cout << "testing operator new & operator delete..." << std::endl;

        MyMemory *p1 = new MyMemory();
        delete p1;
        p1 = nullptr;
        std::cout << "++++++++++\n";

        MyMemory *p2 = ::new MyMemory();
        ::delete p2;   // 此处像是调用的标准库的版本
        p2 = nullptr;        
        
 		std::cout << "------------------------------" << std::endl;
        return 0;
    }
}