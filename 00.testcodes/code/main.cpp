#if 0
#include "test_override_final.hpp"
#include "test_scope_enum.hpp"
#include "test_typedef_using.hpp"
#include "test_initializer_list.h"
#include "test_default_parameter.hpp"
#include "test_auto.hpp"
#include "test_decltype.hpp"
#include "test_hybrid.hpp"
#include "test_exception.hpp"
#include "test_exception1.hpp"
#include "test_exception2.hpp"
#include "test_exception_errorprocess.hpp"
#include "test_exception_ctor.hpp"
#include "test_exception_function_try_blocks.hpp"
#include "test_operator_new.hpp"
#include "test_global_operator_new.hpp"
#include "test_operator_new_supply.hpp"
#include "test_initializer_list2.hpp"
#include "test_distinguish_parentheses_braces.hpp"
#include "test_virtual_physics_address.hpp"
#include "test_align.hpp"
#include "test_ebo.hpp"
#include "test_starthis.hpp"
#include "test_friend.hpp"
#include "test_static.hpp"
#endif
#include "test_new.h"
#include "test_swap.hpp"

#include <string>
#include <iostream>

int main()
{
    std::cout << "__cplusplus: " << __cplusplus << std::endl;
#if 0
    test_override_final::main();
    test_scope_enum::main();
    test_typedef_using::main();
    test_initializer_list::main();
    test_default_parameter::main();
    test_new::main();
    std::cout << "test_new::bufSize = " << test_new::bufSize << std::endl;
    test_auto::main();
    test_decltype::main();
    test_hybrid::main();
    test_exception::main();
    test_exception1::main();
    test_exception2::main();
    test_exception_errorprocess::main();
    test_exception_ctor::main();
    test_exception_function_try_blocks::main();
    test_operator_new::main();
    std::cout << "================================================\n";
    testGlobalOperatorNewDelete();
    test_initializer_list2::main();
    test_distinguish_parentheses_braces::main();
    test_operator_new_main();
    test_virtual_physics_address::main();
    test_align::main();
    test_ebo::main();
    test_starthis::main();
    test_friend::main();
    test_static::main();
#endif
    test_swap::main();


    std::cout << "The end." << std::endl;
}
//先分配空间再调用构造函数mech table
