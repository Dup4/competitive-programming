#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, n, Min = 1e9, res = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> x;
		res = max(res, x - Min);
		Min = min(Min, x);
	}
	cout << res << "\n";
	return 0;	
}
