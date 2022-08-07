#pragma once

#include <typeinfo>
#include <iostream>

namespace test_scope_enum
{
    int main()
    {
        std::cout << "test_scope_enum......." << std::endl;

        {
            enum class Color
            {
                black, white, red
            };

            bool white = false;   // 这个white不是enum class Color内

            Color c1 = Color::white;
            auto c2 = Color::white;

            /*enum class sColor : long long { black, white, red };
            enum uColor : long long { black, white, red };*/

            std::cout << typeid(Color::red).name() << std::endl;
        }

        std::cout << "scope_enum pass,----------------------------" << std::endl;

        return 0;
    }
}
