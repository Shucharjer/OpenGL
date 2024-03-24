#pragma once
#include <iostream>
class Logger
{
    public:
    static void Output(void) {}
    template<class T, class ...OtherArgs>
    static void Output(T val, OtherArgs... others)
    {
    #ifdef _DEBUG
        std::cout << val;
    #endif
        Output(others...);
    }
};