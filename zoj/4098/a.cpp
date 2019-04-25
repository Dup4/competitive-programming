#include <bits/stdc++.h>
using namespace std;

/*
	S^2 = (x_1^2 + x_2^2 + ... + x_k^2) / k - ave^2
*/

#define ll long long
#define N 110
const ll p = (ll)1e9 + 7;
int n, m;
ll w[N], Bit[N], zero_sum, zero_sum2, zero_case, zero_cnt;   
ll Case, sum, sum2;
vector < vector <int> > G;
vector <int> zero;
ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res = res * base % p;
		}
		base = base * base % p;
		n >>= 1;
	}
	return res; 
}
int used[N];  
void DFS(int u, ll val) {
	for (int i = u + 1; i <= n; ++i) if (!used[i]) {
		DFS(i, val); 
	    break;	
	}
	for (auto &v : G[u]) {   
		++used[v];
	}
	(val *= w[u]) %= p;
	(Case += zero_case) %= p;  
	(sum += val * zero_sum % p) %= p;
    (sum2 += val * val % p * zero_sum2 % p) %= p;	
	for (int i = u + 1; i <= n; ++i) if (!used[i]) {   
		DFS(i, val); 
		break;
	}
	for (auto &v : G[u]) {
		--used[v];
	}
}

void init() {
	G.resize(n + 1);
	zero.clear();
	memset(used, 0, sizeof used);
}
int main() {
	Bit[0] = 1;
	for (int i = 1; i < N; ++i) {
		(Bit[i] = Bit[i - 1] << 1) %= p;
	}  
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", w + i);
		}
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1; i <= n; ++i) if (G[i].empty()) {
			zero.push_back(i);
			used[i] = 1;
			if ((int)zero.size() >= 18) {
				break;
			}
		}
		zero_cnt = (int)zero.size();    
		zero_case = Bit[zero_cnt]; zero_sum = zero_sum2 = 0;   
		Case = zero_case; sum = sum2 = 0;
		for (int i = 0; i < zero_case; ++i) {
			ll tot = 1;
			for (int j = 0; j < zero_cnt; ++j) {
				if ((i >> j) & 1) {
					(tot *= w[zero[j]]) %= p;
				}
			}
			(zero_sum += tot) %= p;
			(zero_sum2 += tot * tot % p) %= p;
		}
		sum = zero_sum; sum2 = zero_sum2;
	    for (int i = 1; i <= n; ++i) if (!used[i]) { 
			DFS(i, 1);
			break;
		}
		ll inv = qmod(Case, p - 2);
		printf("%lld\n", (sum2 * inv % p - sum * sum % p * inv % p * inv % p + p) % p);
	}
	return 0;
}
