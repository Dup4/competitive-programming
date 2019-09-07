#include <bits/stdc++.h>
using namespace std;

int ok(int x) {
	int res = 0;
	while (x) {
		res += x % 2;
		x /= 2;
	}
	return res;
}

int main() {
	int w; cin >> w; 
	for (int i = 2; i <= w; i += 2) {
		if (ok(i) && ok(w - i)) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}

