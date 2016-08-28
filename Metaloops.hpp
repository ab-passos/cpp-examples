#ifndef METALOOPS_HPP
#define METALOOPS_HPP

#include <iostream>

template<int start, int end>
struct print_range
{
	static void eval(void){
		std::cout << start << " \n";
		print_range<start + 1, end>::eval();
	}
};

template<int end>
struct print_range<end, end>
{
	static void eval(void){
		std::cout << end << " \n";
	}
};

#endif