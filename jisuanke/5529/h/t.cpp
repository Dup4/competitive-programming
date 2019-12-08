#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];

int main() {
	set<int> s;
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		s.clear();
		for (int S = 0; S < (1 << n); ++S) {
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				if (S & (1 << i)) {
					sum += a[i];
				}
			}
			s.insert(sum);
		}
		for (auto it : s) {
			cout << it << " ";
		}
		cout << endl;
	}
	return 0;
}
