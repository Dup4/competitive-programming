#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
const ull basep = 31;
int n, m, lens, lent;
vector <string> s, t;
vector <ull> Ht;
map <ull, int> used, has;    
ull qmod(ull base, int n) {
	ull res = 1;
	while (n) {
		if (n & 1) {
			res = res * base;
		}
		base = base * base;
		n >>= 1;
	}
	return res;
}
void Hash(vector <string> &s, vector <ull> &H, int sze, int len, ull base) {
	H.clear(); H.resize(sze); 
	for (int i = 0; i < sze; ++i) {
		H[i] = 0;
		ull tmp = base;	
		for (int j = 0; j < len; ++j) {
			H[i] = H[i] + tmp * s[i][j];
			tmp *= basep;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m >> lens >> lent) {
		s.clear(); s.resize(n);
		t.clear(); t.resize(m); 
		Ht.clear(); Ht.resize(m);
		for (int i = 0; i < n; ++i) cin >> s[i];
		for (int i = 0; i < m; ++i) cin >> t[i];
		Hash(t, Ht, m, lent, qmod(basep, lens - (lens + lent) / 2 + 1));
		has.clear(); for (int i = 0; i < m; ++i) ++has[Ht[i]];
		int need = (lens + lent) / 2;
		ll res = 0;
		ull D = qmod(basep, need);
		for (int i = 0; i < n; ++i) {
			used.clear(); 
		    ull L = 0, R = 0, base;	
			base = basep;
			for (int j = need; j < lens; ++j) {
				R = R + base * s[i][j];
				base *= basep;
			}
			base = basep;
			for (int j = 0; j < need; ++j) {
				L = L + base * s[i][j];
				base *= basep;    
			}
			for (int j = need - 1; j >= 0; --j) { 
				if (used.find(L) == used.end() && has.find(L - R) != has.end()) {
					used[L] = 1;
					res += has[L - R];	
				}
				L -= D * s[i][j];
				L *= basep;
				L += basep * s[i][j]; 
			}
		}
		cout << res << "\n";
	}
	return 0;
}
