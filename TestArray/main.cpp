#include <iostream>
#include "map.h"
#include <string>
#include <chrono>
#include <map>

using namespace std;

int main()
{
	const int len = 3;
	int numbers[len];
	for (int i = 0; i < len; i++) {
		numbers[i] = i;
	}
	
	auto start_time = std::chrono::steady_clock::now();
	Node* test = NULL;
	test = insert(test, numbers[0], numbers[0]);
	
	for (int i = 1; i < len; i++)
		insert(test, numbers[i], numbers[i]);
	for (int i = 0; i < len; i += 2)
		remove(test, numbers[i]);
	for (int i = 1; i < len; i += 2) {
		find(test,numbers[i]);
	}
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	if (!isBalanced(test)) {
		cout << "Tree is not balanced!" << endl;
	}
	/*
	for (int i = 1; i < len; i += 2) {
		if (test.find(numbers[i]) != i) {
			cout << "Wrong value for " << i << endl;
		}
	}
	*/
	start_time = std::chrono::steady_clock::now();
	map<int, int> test1;
	for (int i = 0; i < len; i++)
		test1[numbers[i]] = numbers[i];
	for (int i = 0; i < len; i += 2)
		test1.erase(numbers[i]);
	for (int i = 1; i < len; i += 2)
		test1.find(numbers[i]);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns_Map.count() << endl << elapsed_ns_map.count() << endl;
}