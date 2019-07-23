#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define ull unsigned long long 
int n, m, d[30], a[N];
string s[N]; 

map<ull, int> mp;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); 
	while (cin >> n >> m) {
		mp.clear();
		for (int i = 0; i < 26; ++i) cin >> d[i];
		for (int i = 1; i <= n; ++i) cin >> s[i];
		for (int i = 1; i <= n; ++i) {
			ull Hash = 0;
			ull base = 31;
			a[i] = 1;
			for (auto it : s[i]) {
				Hash += base * it;
				++mp[Hash]; 
				base *= 31;
				a[i] = 1ll * a[i] * d[it - 'a'] % m;
			}
		}
		for (int i = 1; i <= n; ++i) {
			ull Hash = 0;
			ull	base = 31;
			int tmp = 1;
			ll res = 0;
			for (int j = 0, len = s[i].size(); j < len - 1; ++j) {
				Hash += base * s[i][j];
				base *= 31;
				tmp = 1ll * tmp * d[s[i][j] - 'a'] % m;
				if (tmp > a[i]) res += mp[Hash];
			}
			printf("%lld%c", res, " \n"[i == n]);	
		}
	}
	return 0;
}
