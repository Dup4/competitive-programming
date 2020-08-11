#include <bits/stdc++.h>
using namespace std;



int main() {
	int a, b[5]; cin >> a;
	int i = 0;
	while (a) {
		b[++i] = a % 10;
		a /= 10;
	}	
	for (int i = 1; i < 5; ++i) {
		b[i] += 9;
		b[i] %= 10;
	}
	swap(b[3], b[4]);
	swap(b[1], b[2]);
	for (int i = 1; i < 5; ++i) {
		cout << b[i];
	}
	cout << endl;
	return 0;
}
