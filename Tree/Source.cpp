#include<iostream>
#include<vector>
#include"Header.h"


int main() {
	int x, top_d;
	std::cin >> top_d;
	SearchTree<int> a{top_d};
	for (int i = 1; i < 10000; i++) {
		x = i;
		a.push(x);
	}
	SearchTree<int> b(a);
	for (int i = 1; i < 10000; i++) {
		a.remove(i);
	}
	std::cout << b.exists(10000) << std::endl;
}




















