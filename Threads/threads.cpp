#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define ull unsigned long long
//typedef unsigned long long ull;

//#include <__msvc_all_public_headers.hpp>

bool is_even(ull x) {
	return (x % 2 == 0);
}

bool is_odd(ull x) {
	return !is_even(x);
}

typedef bool (*Checker) (ull);

void AddSome(const ull start, const ull end, Checker check1, ull& counter1, Checker check2, ull& counter2) {
	
	for (unsigned long long i = start; i < end; i++) {
		if (check1 != NULL && check1(i) == true) {
			counter1 += i;
		}
		if (check2 != NULL && check2(i) == true) {
			counter2 += i;
		}
	}
}

void FindEven( ull start,  ull end, ull &counter) {
	if (start & 1) start++;
	for (ull i = start; i <= end; i += 2) {
		counter += i;
	}
}

void FindOdd(ull start, ull end, ull& counter) {
	if (start % 2 == 0) start++;
	for (ull i = start; i <= end; i += 2) {
		counter += i;
	}
}

int main()
{
	ull start = 0, end = 1900000000;
	ull even = 0, odd = 0;

	auto start_time = std::chrono::high_resolution_clock::now();

	/*std::vector<std::pair<ull&, Checker> > calcs = {
		{even, is_even},
		{odd, is_odd}
	};*/

	std::thread operation_1 (FindEven, start, end, even);
	std::thread operation_2 (FindOdd, start, end, odd);

    operation_1.join();
    operation_2.join();
	//AddSome(start, end, is_even, even, is_odd, odd);
	// FindEven(start, end, even);
	// FindOdd(start, end, odd);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

	std::cout << even << " " << odd << std::endl;
	std::cout << duration.count() / 1e6 << std::endl;

	return 0;
}