#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main() {
	int n, j2, sum, third, s, flag;
	cin >> n;
	vector<int> t1(2 * n);//out
	vector<int> t2(n);//in
	vector<int> temp(2 * n);
	for (int i = n; i < 2 * n; i++) {
		temp[i] = 1;
	}
	do {
		t1.assign(temp.begin(), temp.end());
		s = 0;
		j2 = 0;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i]) {
				t2[j2] = i + 1;
				s += t2[j2];
				j2++;
			}
		}
		do {
			flag = 0;
			if (s % n == 0) {
				sum = 1 + 2 * n + s / n;
				for (int x = 0; x < n; x++) {
					third = sum - t2[x] - t2[(x + 1) % n];
					if ((third <= 0) || (third > 2 * n)) {
						flag = 1;
						break;
					}
					if (t1[third - 1] == 0) t1[third - 1] = 2;
					else if (t1[third - 1] != 0) {
						flag = 1;
						break;
					}
				}
			}
			else break;
			if (flag == 1) continue;
			for (int x = 0; x < n; x++) {
				third = sum - t2[x] - t2[(x + 1) % n];
				cout << "(" << t2[x] << ", " << t2[(x + 1) % n] << ", " << third << ") ";
			}
			cout << endl;
			for (int x = 0; x < n; x++) {
				third = sum - t2[x] - t2[(x + 1) % n];
				cout << "(" << third << ", " << t2[(x + 1) % n] << ", " << t2[x] << ") ";
			}
			cout << endl;
		} while (next_permutation(t2.begin(), t2.end()));
	} while (next_permutation(temp.begin(), temp.end()));
}









