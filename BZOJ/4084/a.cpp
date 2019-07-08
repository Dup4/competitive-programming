#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
int n, m, lens, lent;
vector <string> s, t;
vector <vector<ull>> Hs, Ht;
map <ull, int> used, has;    
void Hash(vector <string> &s, vector <vector<ull>> &H, int sze, int len) {
	ull base = 31;
	for (int i = 0; i < sze; ++i) {
		H[i].clear(); H[i].resize(len);
		for (int j = 0; j < len; ++j) {
			H[i][j] = H[i][j - 1] + base * (s[i][j] - 'a');   
			base *= 31;
		}
	}
}
ull getHash(vector <ull> &H, int l, int r) {
	ull R = H[r];
	ull L = 0;
	if (l) L = H[l - 1];
	return R - L;  
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> m >> lens >> lent) {
		s.clear(); s.resize(n);
		t.clear(); t.resize(m); 
	    Hs.clear(); Hs.resize(n);
		Ht.clear(); Ht.resize(m);
		for (auto &it : s) cin >> it;
		for (auto &it : t) cin >> it;	
		Hash(s, Hs, n, lens); Hash(t, Ht, m, lent);
		has.clear();
		int need = (n + m) / 2;
		int tail = n - need;  
		for (auto it : Ht) ++has[it];
		ll res = 0;
		for (int i = 0; i < n; ++i) {
			used.claer(); 
		    ull HT = getHash(Hs[i], tail - 1, len - 1); 	
			for (int j = 0, j < tail; ++j) {
				if (tail - j >= need) {
					int now = tail - need; 
					if (getHash(Hs[i], now - 1, tail - 1) == HT) {
						res += has[]
					}			
				}
			}
		}
		cout << res << "\n";
	}
	return 0;
}
