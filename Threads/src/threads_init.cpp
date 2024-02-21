#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define ull unsigned long long

void print_some (const char c) {

	for (int i = 0; i < 40; i++) {
		std::cout << c;
	}
}

class Base {
public:
	void operator() (char c) {
		print_some(c);
	}
};

int main()
{
	ull start = 0, end = 19000000000;

	auto start_time = std::chrono::high_resolution_clock::now();

	/*std::vector<std::pair<ull&, Checker> > calcs = {
		{even, is_even},
		{odd, is_odd}
	};*/

	auto fun = [](char c) {
		print_some(c);
	};

	// Function Pointer
	std::thread operation_2 (print_some, '+');
	std::thread operation_5 (print_some, '^');

	// Lambda Expression with auto
	std::thread operation_1 (fun, '-');
	

	// Lambda Expression without auto
	std::thread operation_3 ([](char c) {
		print_some(c);
	}, '~');

	// Functor
	std::thread operation_4 ((Base()), '=');

	

    operation_1.join();
    operation_2.join();
	operation_3.join();
	operation_4.join();
	operation_5.join();
	//AddSome(start, end, is_even, even, is_odd, odd);
	//FindEven(start, end);
	//FindOdd(start, end);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

	std::cout << duration.count() / 1e6 << std::endl;

	return 0;
}