#include "fibonacci.hpp"
#include <iostream>

int main()
{
	std::cout << "Fibonacci(4) = ";
    std::cout << Fibonacci<4>::value;
    std::cout << std::endl;

    std::cout << "Fibonacci(5) = ";
    std::cout << Fibonacci<5>::value;
    std::cout << std::endl;

    std::cout << "Fibonacci(6) = ";
    std::cout << Fibonacci<6>::value;
    std::cout << std::endl;


    std::cout << "Fibonacci(7) = ";
    std::cout << Fibonacci<7>::value;
    std::cout << std::endl;


    std::cout << "Fibonacci(8) = ";
    std::cout << Fibonacci<8>::value;
    std::cout << std::endl;


    std::cout << "Fibonacci(9) = ";
    std::cout << Fibonacci<9>::value;
    std::cout << std::endl;

	return 0;
}