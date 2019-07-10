#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define N 1000010
int n, m, s[N], t[N];
ull Hash[N];
ull Hs[N], Ht[N];
int sze_s[N], sze_t[N]; 
unordered_map <ull, int> mp;
ll diff, res;

void add(ull x) {
	--mp[x];
	if (mp[x] == 0) --diff;
}

void del(ull x) {
	if (mp[x] == 0) ++diff;
	++mp[x];
}

void init() {
	ull base = 31;
	for (int i = 1; i <= 1000000; ++i) {
		Hash[i] = base;
		base *= 31;
	}
}
int main() {
	init();
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(Hs, 0, sizeof Hs);
		memset(ht, 0, sizeof Ht);
		memset(sze_s, 0, sizeof sze_s); 
		memset(sze_t, 0, sizeof sze_t);
		mp.clear(); 
		for (int i = 1; i <= n; ++i) scanf("%d", s + i);
		for (int i = 1; i <= m; ++i) scanf("%d", t + i);
		diff = 0, res = 0;
		for (int i = 1; i <= m; ++i) {
			if (sze_t[t[i]]) {
				del(Ht[t[i]]);
				Ht[t[i]] ^= Hash[i];
				add(Ht[t[i]]);
			} else {
				Ht[t[i]] ^= Hash[i];
				add(Ht[t[i]]);
			}
			++sze_t[t[i]];
		}
		for (int i = 1; i <= m; ++i) {
			if (sze_s[s[i]]) {
				del(Hs[s[i]]);
				Hs[s[i]] ^= Hash[i];  	
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
