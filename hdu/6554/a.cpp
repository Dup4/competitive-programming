#include <bits/stdc++.h>
using namespace std;

string s[4] = {
	"1113",
	"2133",
	"2243",	
	"2444"
};

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n % 4 || m % 4) {
			cout << "no response\n";
		} else {
			for (int i = 0; i < n / 4; ++i) {
				for (int _ = 0; _ < 4; ++_) {
					for (int j = 0; j < m / 4; ++j) {
						cout << s[_];	
					}
					cout << "\n";
				}
			}
		}
	}
	return 0;
}
