#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 1e9 + 7;
int n, q;
vector < vector <int> > vec;
void add(ll &x, ll y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &q);
		vec.clear();
		vec.resize(n + 1);
		for (int i = 1, tp, pos; i <= q; ++i) {
			scanf("%d%d", &tp, &pos);
			vec[pos].push_back(tp);
		}
		ll lazy1[4] = {0};
		ll lazy2[4] = {0};
		ll res[4] = {0}; 
		for (int i = 1; i <= n; ++i) {
			add(res[2], lazy1[2]);		
			add(res[3], (2ll * lazy2[3] % p + lazy1[3]) % p);
			add(lazy2[3], lazy1[3]);
			for (auto it : vec[i]) {
				switch (it) {
					case 1:
						add(res[1], 1);
						break;
					case 2 :
						add(lazy1[2], 1);
						add(res[2], 1);
						break;
					case 3 :
						add(lazy1[3], 1);
						add(lazy2[3], 1);
						add(res[3], 1);
						break;
					default :
						assert(0);
				}
			}
			printf("%lld%c", ((res[1] + res[2]) % p + res[3]) % p, " \n"[i == n]);
		}
	}
	return 0;
};
