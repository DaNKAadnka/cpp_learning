#include <iostream>


extern "C" _declspec(dllexport) void HelloWorld();

void HelloWorld() {
	std::cout << "Hello world! " << std::endl;
}