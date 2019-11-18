#include<iostream>
#include<vector>
#include"Header.h"
#include<set>
#include<time.h>
#include<stdio.h>
using std::set;

int main() {
	SearchTree<int> a{-1};
	for (long long int i = 100000; i > 0; --i) {
		a.push(i);
	}
	a.verification();
	set<int> s;
	clock_t start = clock();
	for (long long int i = 100000; i > 0; --i) {
		a.push(i);
	}
	for (long long int i = 100000; i > 0; --i) {
		a.remove(i);
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time measured with myself AVL-tree: " << seconds << std::endl;

	start = clock();
	for (long long int i = 100000; i > 0; --i) {
		s.insert(i);
	}
	for (long long int i = 100000; i > 0; --i) {
		s.erase(i);
	}
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time measured with standart set: " << seconds << std::endl;
	SearchTree<int> b{1};
	b = a;
}




















