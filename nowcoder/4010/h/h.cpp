#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 2e6 + 10, limit = 2e6;
ll n; int m, tot;
struct E { int to, nx, vis; }e[N << 1]; int h[N]; 
void add(int u, int v) { 
	e[tot] = { v, h[u], 0}; h[u] = tot++; 
	e[tot] = { u, h[v], 0}; h[v] = tot++;
} 
vector <int> res;

void dfs(int u) {
	for (int &i = h[u]; i != -1; i = e[i].nx) { 
		if (e[i].vis == 0) {
			int v = e[i].to;
			e[i].vis = 1;
			e[i ^ 1].vis = 1;
			dfs(v); 
			res.push_back(v);
		}
		if (i == -1) break;
	}
}

ll calc(ll x) { 
	if ((x & 1) == 1) return x * (x - 1) / 2 + 1;
	return x * (x - 2) / 2 + (x - 1) + 1; 
}

int main() {
	scanf("%lld", &n);
	ll l = 2, r = 2e9, pos = 1; 
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
		if (calc(mid) <= n) {
			pos = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	if (n > limit) printf("%lld\n", pos);
	else {
		if (m == 1) {
			puts("1\n1");
			return 0;
		}
		m = pos;
		for (int i = 1; i <= m; ++i) h[i] = -1;
		tot = 0;
		res.clear();
		if (m % 2 == 1) {
			for (int i = 1; i <= m; ++i) {
				for (int j = i + 1; j <= m; ++j) {
					add(i, j);
				}
			}	
		} else {
			for (int i = 1; i <= m; ++i) {
				for (int j = i + 1; j <= m; ++j) {
					add(i, j);
				}
			}
			for (int i = 2; i < m; i += 2) {
				add(i, i + 1);
			}
		}
		dfs(1);
		while (res.size() < n) res.push_back(1);;
		printf("%d\n", m);
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", res[i - 1], " \n"[i == n]);
		}
	}
	return 0;
}
