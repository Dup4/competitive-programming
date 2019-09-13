#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	int T; cin >> T;
	while (T--) {
		int n; cin >> n;
		map <vector<int>, int> mp; 
		vector <int> a(n + 1);
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= n; ++i) {
			vector <int> vec;
			int Max = 0;
			for (int j = i; j <= n; ++j) {
				Max = max(Max, a[j]);
				vec.push_back(a[j]);
				mp[vec] = Max;
			}
		}
		ll res = 0;
		for (auto &it : mp) res += it.second;
		cout << res << "\n";
	}
}
