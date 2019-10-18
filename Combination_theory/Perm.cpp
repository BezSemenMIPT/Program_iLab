#include<iostream>
#include<vector>
#include<algorithm>
 
using namespace std;


int main() {
	int n, j1, j2, sum, flag;
	cin >> n;
	vector<int> t1(n);//out
	vector<int> t2(n);//in
	vector<int> temp(2*n);
	for (int i = n; i < 2 * n; i++) {
		temp[i] = 1;
	}
	do {
		j1 = 0;
		j2 = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i]) {
				t2[j2] = i + 1;
				j2++;
			}
			else {
				t1[j1] = i + 1;
				j1++;
			}
		}	
		do {
			flag = 1;
			sum = t2[0] + t2[1] + t1[0];
			for (int k = 1; k < n; k++) {
				if (t2[k] + t2[(k + 1) % n] + t1[k] != sum) {
					flag = 0;
					break;
				}
			}
			if (flag == 1) {
				for (int x = 0; x < n; x++) {
					cout << "(" << t1[x] << ", " << t2[x] << ", " << t2[(x + 1) % n] << ") ";
				}
				cout << endl;
				for (int x = 0; x < n; x++) {
					cout << "(" << t1[x] << ", " << t2[(x + 1) % n] << ", " << t2[x] << ") ";
				}
				cout << endl;
			}
		} while (next_permutation(t2.begin(), t2.end()));
	} while (next_permutation(temp.begin(), temp.end()));
}







