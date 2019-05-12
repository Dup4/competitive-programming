#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;

struct node {
	int pos;
	ll val;
	node(){}
	node(int pos, ll val):pos(pos), val(val){}
	bool operator < (const node &other) const {
		return val > other.val;
	}
};

int n, m;
ll d[maxn << 1];
int h[maxn];
int vis[maxn];
priority_queue<node>q;
vector<int>G[maxn];

int main() {
	while(~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; ++i) {
			G[i].clear();
			vis[i] = 0;
		}
		while(!q.empty()) q.pop();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", h + i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", d + i);
			d[i + m] = d[i];
		}
		for (int i = 1; i <= 2 * m; ++i) {
			d[i] += d[i - 1];
		}
		for (int i = 1, k, x; i <= n; ++i) {
			scanf("%d", &k);
			while(k--){
				scanf("%d", &x);
				G[i].push_back(x);
			}
		}
		int lazy = 0;
		int now = 0;
		ll res = 0;
		q.push(node(1, h[1]));
		vis[1] = 1;
		while(!q.empty()) {
			node tmp = q.top();
			ll Min = tmp.val;
			Min -= lazy;
			ll cnt = m * Min / d[m];
			int pos = lower_bound(d + 1 + now, d + 1 + 2 * m, tmp.val - lazy) - d;
			lazy += cnt * d[m] + d[pos + 1] - d[now];
			res += cnt + pos - now;
			now = (pos + 1) % m;
			while(!q.empty()) {
				node tp = q.top();
				if(tp.val - lazy <= 0) {
					q.pop();
					for (auto it : G[tp.pos]) {
						if(!vis[it]) {
							vis[it] = 1;
							q.push(node(it, h[it] + lazy));
						}
					}
				} else {
					break;
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
