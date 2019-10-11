#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 10;
int n, a[N]; 
void run() {
	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	int l = 1, r = n, pos = n; 
	while (r - l >= 0) {
		int mid = (l + r) >> 1;  
		if (a[mid] >= 0) {
			pos = mid; 
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	int res;
	if (a[1] >= 0) res = a[1];
    else if (a[n] < 0) res = a[n];	
	else {
		res = min(abs(a[pos - 1]), abs(a[pos])); 
	}
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
