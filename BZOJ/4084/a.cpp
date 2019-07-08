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
		for (int j = 0; j < len; ++j) {
			H[i] = H[i] + base * s[i][j];
			base *= basep;
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
		for (auto &it : s) cin >> it;
		for (auto &it : t) cin >> it;	 
		Hash(t, Ht, m, lent, qmod(basep, n - (n + m) / 2 + 1));
		has.clear(); for (auto it : Ht) ++has[it];
		int need = (n + m) / 2;
		int tail = n - need;  
		ll res = 0;
		ull D = qmod(basep, tail);
		for (int i = 0; i < n; ++i) {
			used.claer(); 
		    ull L = 0, R = 0, base;	
			base = basep;
			for (int j = tail; j < n; ++j) {
				R = R + base * s[i][j];
				base *= basep;
			}
			base = basep;
			for (int j = 0; j < tail; ++j) {
				L = L + base * s[i][j];
				base *= basep;
			}
			for (int j = tail - 1; j >= 0; --j) {
				if (has.find(L - R) != has.end()) {
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
