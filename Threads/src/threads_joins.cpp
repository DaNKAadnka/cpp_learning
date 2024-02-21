#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define ull unsigned long long

void run (char& c) {

	for (int i = 0; i < 10; i++) {
		std::cout << c << std::endl;
	}
	c = 'y';

}

int main()
{
	char c = 'x';
	std::thread thr1 (run, std::ref(c));

	std::cout << "main " << c << "\n";
	
	// If main thread is not end up his work by the end of thread working time
	// it will show his work
	thr1.detach();

	std::cout << "main+ " << c << "\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "main++ " << c << "\n";
	return 0;
}