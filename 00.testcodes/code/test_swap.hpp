#pragma once

#include <iostream>
#include <string>

namespace test_swap
{
    class HasPtr{
        friend void swap(HasPtr&, HasPtr&);
    public:
        explicit HasPtr(const std::string& s = std::string(""), int i=0): ps_(new std::string(s)), i_(i){
            
        }
        
        HasPtr(const HasPtr& p): ps_(new std::string(*p.ps_)), i_(p.i_){
            std::cout << "Using copy-ctor.\n";
        }
        
        HasPtr& operator=(const HasPtr& p){
            std::cout << "Using copy-assign operator.\n";
            if(this == &p){return *this;}
            
            delete this->ps_;
            ps_ = new std::string(*p.ps_);
            i_ = p.i_;
            
            return *this;
        }
        
        ~HasPtr(){
            delete ps_;
        }
        
        void showContent(){
            std::cout << i_ << ", " << *ps_ << std::endl;
        }
        
    private:
        std::string *ps_;
        int i_;        
    };
    
    inline void swap(HasPtr& lhs, HasPtr& rhs) {
        std::cout << "HasPtr, Using self-define swap." << std::endl;
        using std::swap;
        swap(lhs.ps_, rhs.ps_);
        swap(lhs.i_, rhs.i_);
    }
    
    class Foo{
    friend void swap(Foo&, Foo&);
    public:    
        Foo() = default;
        Foo(const std::string &s, int i): hp_(s, i){}
        
        void show(){
            hp_.showContent();
        }
    private:
        HasPtr hp_;
    };
    
#if 0
    inline void swap(Foo& a, Foo& b) {
        std::cout << "Foo, Using std::swap." << std::endl;
        
        std::swap(a.hp_, b.hp_);
    }
#endif
    
#if 1
    inline void swap(Foo& a, Foo& b) {
        std::cout << "Foo, Using self-define swap." << std::endl;
        using std::swap;
        swap(a.hp_, b.hp_);
    }
#endif   

    int main()
    {
        std::cout << "test_swap......." << std::endl;

        // HasPtr hp1(std::string("Hello swap1."), 1);
        // HasPtr hp2(std::string("Hello swap2."), 2);
        // hp1.showContent();
        // hp2.showContent();
        // std::cout << "+++++++++\n";
        // swap(hp1, hp2);
        // hp1.showContent();
        // hp2.showContent();
        // 
        // std::cout << "+++++++++\n";

        Foo foo1(std::string("foo1"), 3);
        Foo foo2(std::string("foo2"), 4);
        foo1.show();
        foo2.show();
        swap(foo1, foo2);
        foo1.show();
        foo2.show();

        std::cout << "test_swap pass\n----------------------------" << std::endl;

        return 0;
    }
}
