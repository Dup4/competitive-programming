#include <bits/stdc++.h>
using namespace std;

using psi = pair<string, int>;
#define fi first
#define se second
typedef unsigned long long ull; 
const int N = 1e5 + 10;
const int M = 30;
int n, q, ans[N]; char s[N];
ull base[M];
unordered_map <ull, int> mp;
vector <psi> vec[N];
inline void getHash(int len) {
	ull Hs = 0;
	for (register int i = 1; i < len; ++i) {
		int c = s[i] - 'a' + 1;
		Hs += base[c];
	}
	for (register int i = len; i <= n; ++i) {
		int c = s[i] - 'a' + 1, pre = s[i - len + 1] - 'a' + 1;
		Hs += base[c];
		mp[Hs + base[0] * pre + base[27] * c]++;
		Hs -= base[pre];
	}
}
inline ull get(string &s) {
	ull Hs = 0;
	for (auto &it : s) Hs += base[it - 'a' + 1];
	Hs += base[0] * (s[0] - 'a' + 1) + base[27] * (s.end()[-1] - 'a' + 1);
	return Hs;
}

int main() {
	base[0] = 1;
	for (int i = 1; i < M; ++i) base[i] = base[i - 1] * 19260817;
	ios::sync_with_stdio(false);
	cin.tie(0); 
	int _T; cin >> _T;
	while(_T--) {
		cin >> (s + 1); n = strlen(s + 1); 
		cin >> q;
		for (int i = 1; i <= q; ++i) {
			string s; cin >> s;
			vec[s.size()].push_back(psi(s, i));
		}
		for (int i = 1; i <= n; ++i) if (!vec[i].empty()) {
			mp.clear();
			getHash(i);
			for (auto &it : vec[i]) {
				ull Hs = get(it.fi);
				ans[it.se] = mp[Hs];
			}
			vec[i].clear();
		}
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	} 
	return 0;
}
