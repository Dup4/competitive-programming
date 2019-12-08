#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool gao(int x) {
	int limit = 500; 
	for (ll a = -limit; a <= limit; ++a) {
		for (ll b = a; b <= limit; ++b) {
			for (ll c = b; c <= limit; ++c) {
				ll a3 = a * a * a;
				ll b3 = b * b * b;
				ll c3 = c * c * c;
				ll sum = a3 + b3 + c3;
				if (sum > x) break;
				if (sum == x) {
					cout << a << " " << b << " " << c << endl;
					return true;
				} 
			}
		}
	}
	return false; 
}

int main() {
	int cnt = 0;
	for (int x = 0; x <= 200; ++x) {
		if (!gao(x)) {
			++cnt;
			int y = -12345678;
			cout << y << " " << y << " " << y << endl;
		}
	}	
	cout << cnt << " " << cnt << " " << cnt << endl;
	return 0;
}
