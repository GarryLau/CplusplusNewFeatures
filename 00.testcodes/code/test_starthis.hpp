#if 0
#include <iostream>
#include <typeinfo>
#include <string>

namespace test_starthis {
    
    class Screen{
    public:
        Screen() = default;
        Screen(int x, int y, std::string contents): x_(x), y_(y), contents_(contents), ct_(0){
            std::cout << "Screen ctor with parameter called." << std::endl;
        }
        
        // 类内实现,默认inline
        Screen set(std::string new_contents){
            contents_ = new_contents;
            
            return *this;
        }
        Screen move(int x, int y) {
            x_ = x;
            y_ = y;
            
            return *this;
        }
        
        // 从const函数返回的对象是const对象,因此返回值也需要加const
        const Screen& display() const {
            std::cout << "contents_: " << contents_ << std::endl;
            std::cout << "x_: " << x_ << ", y_: " << y_ << std::endl;
            
            ++ct_;  // 虽然函数是const,但由于ct_被mutable修饰了,因此可以修改ct_
            
            std::cout << "The screen is displayed " << ct_ << " times." << std::endl;
            
            return *this;   // *this是const对象
        }

    private:
        int x_ = 0;
        int y_{0};;
        std::string contents_{"my screen"};
        mutable unsigned int ct_{0};  // 如果想在const成员函数内修改类的某个数据成员,可在该数据成员的声明中加mutable关键字
    };

    auto main() -> int {
        std::cout << "testing test_starthis......\n" << std::endl;

        Screen screen;
        screen.display();
        screen.move(6,6).set("red screen").display();
        screen.display();

		std::cout << "------------------------------" << std::endl;

        return 0;
    }
}
#endif

#if 0
#include <iostream>
#include <string>

namespace test_starthis {
    
    class Screen{
    public:
        Screen() = default;
        Screen(int x, int y, std::string contents): x_(x), y_(y), contents_(contents), ct_(0){
            std::cout << "Screen ctor with parameter called." << std::endl;
        }
        
        // 类内实现,默认inline
        Screen set(std::string new_contents){
            contents_ = new_contents;
            
            return *this;
        }
        Screen move(int x, int y) {
            x_ = x;
            y_ = y;
            
            return *this;
        }
        
        // 从const函数返回的对象是const对象,因此返回值也需要加const
        const Screen& display() const {
            std::cout << "const version -->\n";
            do_display();

            return *this;
        }

        Screen& display() {
            std::cout << "non-const version -->\n";
            do_display();
            
            return *this;
        }
        
        void do_display() const {
            std::cout << "contents_: " << contents_ << std::endl;
            std::cout << "x_: " << x_ << ", y_: " << y_ << std::endl;
            
            ++ct_;
            
            std::cout << "The screen is displayed " << ct_ << " times." << std::endl;           
        }

    private:
        int x_ = 0;
        int y_{0};;
        std::string contents_{"my screen"};
        mutable unsigned int ct_{0};  // 如果想在const成员函数内修改类的某个数据成员,可在该数据成员的声明中加mutable关键字
    };

    auto main() -> int {

        Screen screen1;
        screen1.display();
        const Screen screen2(6, 6, "red screen");
        screen2.display();

        return 0;
    }
}
#endif

#include <iostream>
#include <string>

namespace test_starthis {
    
    class Controller;
    
    class Screen{
    public:
        // Screen() = default; // 没有意义,因为有引用成员,必须在初始化列表中初始化
        Screen(Controller &controller): controller2_(controller){  // 此处Controller &controller不可改成Controller controller
            std::cout << "Screen ctor with parameter called." << std::endl;
        }
        
        void setController(Controller);  // forward declaration的incomplete type可用于函数参数
        Controller getController();      // 也可用于函数返回值

    private:
        //Controller controller_;  // error: field 'controller_' has incomplete type 'test_starthis::Controller'
        Controller* controller1_;   // [RIGHT],可使用指针形式
        Controller& controller2_;   // [RIGHT],可使用引用形式,但要注意构造函数中的入参也必须是引用,因为想要创建类的对象该类必须被定义过,前向声明不是定义
    };

    auto main() -> int {

        // 完成Controller的定义后
        // Controller controller;
        //Screen screen(controller);  

        return 0;
    }
}

