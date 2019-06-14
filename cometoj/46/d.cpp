#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 150010
#define M 131072
#define S 400
#define pii pair <int, int>
#define fi first
#define se second
const int p = 998244353;
int n, m, q, b[N], d[N], vis[N], id[N], fid[N], cnt_id;
set <pii> G[N]; vector <pii> vec; 
int e[N][3];  

template <typename T>
void add(T &x, T y) {
	x += y;
	if (x >= p) {
		x -= p;
	}
}

struct TRIE {
	struct node {
		int son[2];
		int tot;
		node() {
			memset(son, -1, sizeof son);
			tot = 0;
		}
	}t[N * 200]; 
	int rt[S + 10], cnt;
	void init() {
		for (int i = 1; i <= S; ++i) { 
			rt[i] = i;
			t[i] = node();
		}
		cnt = S; 
		t[0] = node();
	}
	void insert(int id, int x, int y) {
		int root = rt[id];
		for (int i = 17; i >= 0; --i) {
			int nx = t[root].son[(x >> i) & 1];  
			if (nx == -1) {
				nx = ++cnt;
				t[nx] = node();
			}
			add(t[nx].tot, y);
			root = nx;
		}
	}
	int query(int id, int x, int y) {
		int res = 0;
		int root = rt[id];
		for (int i = 17; i >= 0; --i) {
			int f = 0 ^ ((x >> i) & 1); 
			if ((y >> i) & 1) {  
				add(res, t[t[root].son[f]].tot);	
			} 
			root = t[root].son[((y >> i) & 1) ^ f];       
		}
		return res; 
	}
}trie;

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		++x; 
		for (; x < N; x += x & -x) {
			add(a[x], v);  
		}
	}
	int query(int x) {
		++x;
		int res = 0;
		for (; x > 0; x -= x & -x) {
			add(res, a[x]); 
		}
		return res;
	}
	int query(int l, int r) {
		return (query(r) - query(l - 1) + p) % p;
	}
}bit;

void init() {
	cnt_id = 0;
	trie.init();
	bit.init();
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
		d[i] = vis[i] = 0;
	}
}
int main() {
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
		}
		for (int i = 1; i <= m; ++i) {
			int &x = e[i][0], &y = e[i][1], &z = e[i][2];  
			scanf("%d%d%d", &x, &y, &z); 
			++d[x]; ++d[y]; 
			add(z, 0);
			G[x].insert(pii(y, z));
			G[y].insert(pii(x, z));
		}
		for (int i = 1; i <= n; ++i) {
			if (d[i] >= S) {
				vis[i] = 1; 
				id[i] = ++cnt_id; 
			    fid[cnt_id] = i;	
			}
		}
		for (int i = 1; i <= n; ++i) if (vis[i]) {
			vec.clear();
			for (auto it : G[i]) {
				if (!vis[it.fi]) {
					trie.insert(trie.rt[id[i]], b[it.fi], it.se); 
				} else {
					vec.push_back(it); 
				}
			} 
		    G[i].clear();	
			for (auto it : vec) {
				G[i].insert(it);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (auto it : G[i]) {
				if (it.fi < i) {
					bit.update(b[i] ^ b[it.fi], it.se); 
				}
			}
		}
		for (int i = 1; i <= m; ++i) {
			if (vis[e[i][0]] < vis[e[i][1]]) {
				swap(e[i][0], e[i][1]);
			}
		}
		int op, x, y, res;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			switch(op) {
				//修改点权
				case 1 :
					for (auto it : G[x]) {
						bit.update(b[x] ^ b[it.fi], (p - it.se) % p); 
						bit.update(y ^ b[it.fi], it.se);
					}
					if (!vis[x]) {
						for (auto it : G[x]) {
							if (vis[it.fi]) {
								trie.insert(trie.rt[id[it.fi]], b[x], (y -it.se + p) % p);
							}
						}		
					}
					b[x] = y;
					break;
				//修改边权
				case 2 :
					add(y, 0);
					if (vis[e[x][0]] == vis[e[x][1]]) {
						bit.update(b[e[x][0]] ^ b[e[x][1]], (y - e[x][2] + p) % p);
						G[e[x][0]].erase(pii(e[x][1], e[x][2]));
						G[e[x][1]].erase(pii(e[x][0], e[x][2]));
						e[x][2] = y;
						G[e[x][0]].insert(pii(e[x][1], e[x][2]));
						G[e[x][1]].insert(pii(e[x][0], e[x][2]));
					} else {
						trie.insert(trie.rt[id[e[x][0]]], b[e[x][1]], (y - e[x][2] + p) % p);
						e[x][2] = y;
					}
					break;
				//询问
				case 3 :
					res = bit.query(x, y); 
					for (int i = 1; i <= cnt_id; ++i) {
						add(res, (trie.query(trie.rt[i], b[fid[i]], y + 1) - trie.query(trie.rt[i], b[fid[i]], x) + p) % p);  
					}
					printf("%d\n", res);
					break;
				default: 
					assert(0);
			}
		}
	}
	return 0;
}
