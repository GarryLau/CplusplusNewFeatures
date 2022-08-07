#if 0  // 示例1
#pragma once

#include <stdexcept>
#include <exception>
#include <iostream>

/*
    可以抛出任何类型的异常,然而,类是最有用的异常类型
    例如：
    1.基本类型及复合类型;
    2.类类型
    使用(类)对象作为异常抛出的好处：
    1.对象的类名称可以传递信息;
    2.对象可以存储信息,包括用于描述异常的字符串.
    (备注:建议按const引用捕获异常)
    
    如果存在未捕获的异常,会调用内建的terminate()函数,这个函数调用<cstdlib>中的abort()终止程序
    
    没有抛出列表的函数可以抛出任何异常。具有noexcept或者空抛出列表throw()的函数不能抛出任何异常。    
*/

namespace test_exception {
    float divide1(float a, float b) {
        if(b == 0){
            //throw "divided by zero.";
            //throw std::invalid_argument("Divide by zero");
            //throw std::exception();
            throw 5;
        }
        return a / b;
    }
    
    float divide2(float a, float b) noexcept/*throw()*/{
        if(b == 0){
            //throw "divided by zero.";
            throw std::invalid_argument("std::invalid_argument, Divide by zero!");
            //throw std::exception();
            //throw 5;
        }
        return a / b;
    }
    
    
#if 1
    float divide3(float a, float b) throw(int, std::invalid_argument){  // 表示只可抛出int, std::invalid_argument两种类型的异常
        if(b == 0){
            //throw "divided by zero.";  // 此种类型无法抛出
            throw std::invalid_argument("std::invalid_argument, Divide by zero!"); // 可抛出此种类型
            //throw std::exception();   // 此种类型无法抛出
            //throw 5;                  // 可抛出此种类型
        }
        return a / b;
    }
#endif
        

    auto catchSample1() -> void {
        int a = 10;
        int b = 0;

        try {
            std::cout << divide1(a, b) << std::endl;
        }
        catch(const char* e){
             std::cout << e << std::endl;
        }
        catch(const std::invalid_argument& e){
            std::cout << e.what() << std::endl;
        }
        catch(const std::exception& e){  // 增加const属性不会影响匹配的目的,即此句与std::exception& e均可匹配std::exception类型的异常
            std::cout << "+++" << e.what() << "+++" << std::endl;
        }
        catch(int e){
            std::cout << "catching integer\n";
        }
        catch(...){  // 三个点时与所有异常类型匹配的通配符,可以使用这一技术确保捕获所有可能的异常
            std::cout << "unknow exception" << std::endl;
        }
    }
    
    auto catchSample2() -> void {
        int a = 10;
        int b = 0;

        std::cout << "entering catchSample2()...............\n";
        try {
            std::cout << divide2(a, b) << std::endl;
        }
        catch(const std::invalid_argument& e){
            std::cout << e.what() << std::endl;
        }
        catch(...){
            std::cout << "unknow exception" << std::endl;
        }
        std::cout << "exiting catchSample2()...............\n";
    }    

    auto main() -> void {
        std::cout << "testing exception......" << std::endl;
        
        catchSample1();
        catchSample2();
        
        std::cout << "--------------------------------------\n";
    }
}
#endif

#if 0  // 示例2
#pragma once

#include <stdexcept>
#include <exception>
#include <iostream>

namespace test_exception {
    float divide(float a, float b) {
        if(b == 0){
            throw std::invalid_argument("Divide by zero");
            //throw std::exception();
        }
        return a / b;
    }
    
    auto catchSample() -> void {
        int a = 10;
        int b = 0;

        try {
            std::cout << divide(a, b) << std::endl;
        }
        catch(const std::exception& e){
            std::cout << "+++" << e.what() << "+++" << std::endl;
        }
        catch(const std::invalid_argument& e){
            std::cout << e.what() << std::endl;
        }        
        catch(...){
            std::cout << "unknow exception" << std::endl;
        }
    }
 
    auto main() -> void {
        std::cout << "testing exception......" << std::endl;
        
        catchSample();
        
        std::cout << "--------------------------------------\n";
    }
}
#endif


/*
    当某段代码抛出一个异常的时候,被抛出的值或者对象被复制,
    即通过使用复制构造函数从旧对象构造新对象;复制是必须的,
    因为原始对象在堆栈中的位置较高,因此可能在异常被捕获之前超出作用域(因此会被销毁,其所占的内存会被回收)
    因此,如果编写的类的对象作为异常抛出,对象必须能被复制,这意味着如果动态分配了内存,必须编写析构函数、复制构造函数以及赋值运算符
    
    提示：作为异常抛出的对象至少会按值复制一次，按引用捕获异常可以避免不必要的复制
*/
#pragma once

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>

namespace test_exception {
    class FileError : public std::runtime_error {
    public:    
        FileError(const std::string& filename): filename_(filename), msg_(""), std::runtime_error(""){}
    virtual const char* what() const noexcept override{return msg_.c_str();}
    protected:
        std::string filename_, msg_;
    };
    
    class FileOpenError : public FileError {
    public:
        FileOpenError(const std::string& filename): FileError(filename){
            msg_ = std::string("Unable to open ") + filename_;
        }
    };

    class FileReadError : public FileError {
    public:
        FileReadError(const std::string& filename, int linenumber): FileError(filename), linenum_(linenumber){
            msg_ = std::string("Exception occurs in file ") + filename_ + std::string(", line ") + std::to_string(linenum_);
        }
    protected:
        int linenum_;
    };
 
    auto main() -> void {
        std::cout << "testing exception......" << std::endl;

        std::string filename("../doc/daisy.txt");
        std::ifstream in_file(filename);
        try {
            if(in_file.fail()){
                throw FileOpenError(filename);
            }
            
            std::string line;
            int linenum = 0;
            while(std::getline(in_file, line)){
                linenum++;
                std::cout << line << std::endl;
            }
            if(!in_file.eof()){
                in_file.close();
                throw FileReadError(filename, linenum);
            }
        }
        catch(const FileOpenError& e){
            std::cout << "Line: " << __LINE__ << ", " << e.what() << std::endl;
        }
        catch (const FileReadError& e){
            std::cout << "Line: " << __LINE__ << ", " << e.what() << std::endl;
        }
        catch(...){
            std::cout << "unknow error occurs." << std::endl;
        }
        in_file.close();
        
        std::cout << "--------------------------------------\n";
    }
}

