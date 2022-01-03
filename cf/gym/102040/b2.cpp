#include <bits/stdc++.h>

using namespace std;

#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl;}
template<class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }


using ll = long long;

const int N = 20;

struct node {
	ll sum, num;
	ll cnt[N];

	node() {
		sum = num = 0;
		memset(cnt, 0, sizeof cnt);
	}
}dp[N];

int vis[N];
int a[N];

node gogogo(int pos, int st, int limit) {
	if (!limit && vis[pos]) return dp[pos];
	if (pos == 1) {
		node res = node();
		res.num = 1;
		return res;
	}
	node res = node();
	int up = limit ? a[pos - 1] : 9;
	for (int i = 0; i <= up; ++i) {
		node other = gogogo(pos - 1, i, limit && i == up);
		res.sum += other.sum;
		for (int j = i + 1; j <= 9; ++j) res.sum += other.cnt[j];
		for (int j = 0; j <= 9; ++j) res.cnt[j] += other.cnt[j];
		res.cnt[i] += other.num;
		res.num += other.num;
	}
	vis[pos] = 1;
	dp[pos] = res;
	return res;
}

ll gao(ll x) {
	if (x < 10) return 0;
	for (int i = 0; i < N; ++i) dp[i] = node();
	memset(vis, 0, sizeof vis);
	ll res = 0;
	*a = 0;
	ll tmp = x;
	while (tmp) {
		a[++*a] = tmp % 10;
		tmp /= 10;
	}
	for (int i = 1; i <= *a; ++i) {
		int up = (i == *a ? a[i] : 9);
		for (int j = 1; j <= up; ++j) {
			node other = gogogo(i, j, i == *a && j == a[i]);
			res += other.sum;
			for (int k = j + 1; k <= 9; ++k) {
				res += other.cnt[k];
			}
		//	dbg(i, j, res);
		}
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		ll l, r;
		scanf("%lld %lld", &l ,&r);
		printf("Case %d: %lld\n", cas, gao(r) - gao(l - 1));
	}
	return 0;
}
