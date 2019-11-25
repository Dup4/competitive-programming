#include <bits/stdc++.h>
using namespace std;
#define N 10000010
long long b[156255];

int main() {
	int n;
	cin >> n;
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		if (x >= 1 && x <= 10000000) {
			b[x] = 1;
		}
	}
	cout << -1 << endl;	
	return 0;
}
