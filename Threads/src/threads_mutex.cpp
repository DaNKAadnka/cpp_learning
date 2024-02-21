#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

#define ull unsigned long long

std::mutex m;
std::vector <int> x;

void run () {
	for (int i = 0; i < 1000; i++) {
		m.lock();
		x.push_back(i);
		m.unlock();
	}

}

int main () {

	std::thread thr1 (run);
	std::thread thr2 (run);

	thr1.join();
	thr2.join();

	// x should be 200
	for (auto it : x) {
		std::cout << it << "\n";
	}
	// But it works correctly. There are no promised race condictions. That`s odd.
}