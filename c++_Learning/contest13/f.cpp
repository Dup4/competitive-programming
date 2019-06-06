#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; cin >> T;
	while (T--) {
		int n, i, j; cin >> n >> i >> j;
		cout << ((n & (1 << i)) | ((n & (1 << j))) ^ (1 << j)) << endl;
	}
	return 0;
}
