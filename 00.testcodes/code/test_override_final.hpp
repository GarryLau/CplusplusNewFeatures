#pragma once

#include <iostream>
#include <string>

namespace test_override_final
{
    struct BaseA {int val_; };
    struct DerivedA : public BaseA {std::string name_;};

    struct BaseY
    {
        virtual BaseA* foo(){return nullptr;}
        virtual BaseA foo1(){return BaseA();}
        virtual DerivedA* foo2(){return nullptr;}
        virtual void foo3(DerivedA *){}
        virtual void foo4(BaseA*){}
        virtual int bar(){return 0;}
        virtual void bar1(int){}
        virtual void bar2(int){}
    };

    struct DerivedY : BaseY
    {
        virtual DerivedA* foo() override {return nullptr;}   // [RIGHT] can be override

        virtual void bar1(int) override final {} // [RIGHT] 是虚函数还是用final矛盾吗？不矛盾，那是因为DerivedY想重写BaseY中的bar1所以用virtual，但不想DerivedY的子类重写DerivedY中的bar1所以加上了final
        // virtual void bar1(int) final override {} //  final与override顺序无关

        // foo1无法override是因为虽然DerivedA*转为BaseA*是协变，但DerivedA转BaseA不是协变
        //virtual DerivedA foo1() override {}  //! 错误C2555“test_override_final::DerivedY::foo1”: 重写虚函数返回类型有差异，且不是来自“test_override_final::BaseY::foo1”的协变

        // foo2无法override的原因同：可以将子类变量地址赋给父类指针；不可以将父类变量地址赋给子类指针，即可以协变但不能逆变
        //virtual BaseA* foo2() override {}     //! 错误C2555“test_override_final::DerivedY::foo2”: 重写虚函数返回类型有差异，且不是来自“test_override_final::BaseY::foo2”的协变

        //virtual long bar() override{}       //! 错误C2555“test_override_final::DerivedY::bar”: 重写虚函数返回类型有差异，且不是来自“test_override_final::BaseY::bar”的协变

        // 下面三个无法进行override的原因是函数的入参没有满足“完全一致”，即使满足协变也不行，必须完全一致
        //virtual void foo3(BaseA *) override {}  //! 错误C3668“test_override_final::DerivedY::foo3”: 包含重写说明符“override”的方法没有重写任何基类方法
        //virtual void foo4(DerivedA*) override {} //! 错误C3668“test_override_final::DerivedY::foo4”: 包含重写说明符“override”的方法没有重写任何基类方法
        //virtual void bar2(long) override{}  //! 错误C3668“test_override_final::DerivedY::bar2”: 包含重写说明符“override”的方法没有重写任何基类方法
    };
        
    // 综上，关于重写，1.函数的入参，不管是基本类型还是类类型，必须完全一致，对于类类型满足协变也不行，必须”完全一致“
    //                 2.函数的返回值，如果是基本类型则必须完全一致，如果是类类型可以放宽到协变


    auto main() -> int
    {
        std::cout << "test_override_final......." << std::endl;


        std::cout << "override_final pass,----------------------------" << std::endl;
        
        return 0;
    }
}
