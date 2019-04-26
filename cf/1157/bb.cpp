#include <bits/stdc++.h>
using namespace std;

int n;
int f[110];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		string s;
		cin >> s;
		for (int i = 1; i <= 9; ++i) {
			cin >> f[i];
		}
		int pos = n + 1;
		for (int i = 0; i < n; ++i) {
			int x = s[i] - '0';
			if (f[x] > x) {
				pos = i;
				break;
			}
		}
		for (int i = pos; i < n; ++i) {
			int x = s[i] - '0';
			if (f[x] < x) {
				break;
			}
			s[i] = f[x] + '0';
		}
		cout << s << "\n";
	}
	return 0;
}

