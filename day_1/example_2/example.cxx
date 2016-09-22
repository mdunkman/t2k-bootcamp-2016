//
// bootcamp/day_1/example_2/example.cxx
//
// What else, but hello world?
//
#include <iostream>
#include <string>

#include "hello.h"

int main()
{
    std::string message = bootcamp::Hello();
    std::cout << message << "\n";
    return 0;
}

