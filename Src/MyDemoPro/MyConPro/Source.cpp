#include <iostream>
#include "Header.h"

void mytest()
{
	int a = 100;
	int b = 20;

	std::cout << "a = " << a << ", b = " << b << "\n";

	std::cout << "a + b = " << add(a,b) << std::endl;
	std::cout << "a - b = " << sub(a, b) << std::endl;
	std::cout << "max = " << getmax(a, b) << std::endl;
	std::cout << "min = " << getmin(a, b) << std::endl;
}



int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int getmax(int a, int b)
{
	return (a > b ? a : b);
}

int getmin(int a, int b)
{
	return (a > b ? b : a);
}


