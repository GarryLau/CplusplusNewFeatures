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

        virtual void bar1(int) override final {} // [RIGHT] ���麯��������finalì���𣿲�ì�ܣ�������ΪDerivedY����дBaseY�е�bar1������virtual��������DerivedY��������дDerivedY�е�bar1���Լ�����final
        // virtual void bar1(int) final override {} //  final��override˳���޹�

        // foo1�޷�override����Ϊ��ȻDerivedA*תΪBaseA*��Э�䣬��DerivedAתBaseA����Э��
        //virtual DerivedA foo1() override {}  //! ����C2555��test_override_final::DerivedY::foo1��: ��д�麯�����������в��죬�Ҳ������ԡ�test_override_final::BaseY::foo1����Э��

        // foo2�޷�override��ԭ��ͬ�����Խ����������ַ��������ָ�룻�����Խ����������ַ��������ָ�룬������Э�䵫�������
        //virtual BaseA* foo2() override {}     //! ����C2555��test_override_final::DerivedY::foo2��: ��д�麯�����������в��죬�Ҳ������ԡ�test_override_final::BaseY::foo2����Э��

        //virtual long bar() override{}       //! ����C2555��test_override_final::DerivedY::bar��: ��д�麯�����������в��죬�Ҳ������ԡ�test_override_final::BaseY::bar����Э��

        // ���������޷�����override��ԭ���Ǻ��������û�����㡰��ȫһ�¡�����ʹ����Э��Ҳ���У�������ȫһ��
        //virtual void foo3(BaseA *) override {}  //! ����C3668��test_override_final::DerivedY::foo3��: ������д˵������override���ķ���û����д�κλ��෽��
        //virtual void foo4(DerivedA*) override {} //! ����C3668��test_override_final::DerivedY::foo4��: ������д˵������override���ķ���û����д�κλ��෽��
        //virtual void bar2(long) override{}  //! ����C3668��test_override_final::DerivedY::bar2��: ������д˵������override���ķ���û����д�κλ��෽��
    };
        
    // ���ϣ�������д��1.��������Σ������ǻ������ͻ��������ͣ�������ȫһ�£���������������Э��Ҳ���У����롱��ȫһ�¡�
    //                 2.�����ķ���ֵ������ǻ��������������ȫһ�£�����������Ϳ��Էſ�Э��


    auto main() -> int
    {
        std::cout << "test_override_final......." << std::endl;


        std::cout << "override_final pass,----------------------------" << std::endl;
        
        return 0;
    }
}
