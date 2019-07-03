#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
#define S 20000
#define pii pair <int, int>
#define fi first
#define se second
const int p = 998244353;  
int n, m, q, b[N], d[N], vis[N], id[N], fid[N], cnt_id; 
set <pii> G[N]; vector <pii> vec;  
int e[N][3];   
void add(int &x, int y) {
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
	int rt[N], cnt;
	void init() {
		for (int i = 1; i <= S; ++i) { 
			rt[i] = i;
			t[i] = node();  
		}
		cnt = S; 
		t[0] = node(); 
	}
	void insert(int id, int x, int y) {
		int root = rt[id], nx; 
		for (int i = 17; i >= 0; --i) {  
			int f = (x >> i) & 1;
			nx = t[root].son[f];  
			if (nx == -1) {
				nx = ++cnt;
				t[nx] = node();
				t[root].son[f] = nx;
			}
			root = nx;
			add(t[root].tot, y);
		}
	}
	int query(int id, int x, int y) {
		int res = 0;
		int root = rt[id], nx;
		for (int i = 17; i >= 0; --i) {
			int f = ((x >> i) & 1); 
			int g = ((y >> i) & 1); 
			if (g) {   
				nx = t[root].son[f];
				if (nx != -1) {
					add(res, t[nx].tot);	
				}
			}
		    nx = t[root].son[g ^ f];
			if (nx == -1) break;	
			root = nx;
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
		    z %= p;	
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
					trie.insert(id[i], b[it.fi], it.se); 
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
				if (it.fi < i && vis[i] == vis[it.fi]) {
					bit.update(b[i] ^ b[it.fi], it.se); 
				}
			}
		}
		for (int i = 1; i <= m; ++i) {
			if (vis[e[i][0]] < vis[e[i][1]]) {
				swap(e[i][0], e[i][1]);
			}
		}
		int op, x, y, u, v, w;
		int res;
		while (q--) {
			scanf("%d%d%d", &op, &x, &y);
			switch(op) {
				//修改点权
				case 1 :
					y %= p;
					for (auto it : G[x]) if (vis[x] == vis[it.fi]) {
						bit.update(b[x] ^ b[it.fi], (p - it.se) % p); 
						bit.update(y ^ b[it.fi], it.se);
					}
					//小点
					if (!vis[x]) {
						for (auto it : G[x]) {  
							if (vis[it.fi]) {
								trie.insert(id[it.fi], b[x], (p - it.se) % p);
								trie.insert(id[it.fi], y, it.se);      
							} 
						}		
					}
					b[x] = y;
					break;
				//修改边权
				case 2 :
					y %= p;
					u = e[x][0], v = e[x][1], w = e[x][2];
					if (y == w) break;
					if (vis[u] == vis[v]) { 
						bit.update(b[u] ^ b[v], (y - w + p) % p); 
						G[u].erase(pii(v, w));
						G[v].erase(pii(u, w));
						G[u].insert(pii(v, y));
						G[v].insert(pii(u, y));  
					} else {
						trie.insert(id[u], b[v], (y - w + p) % p);
						G[v].erase(pii(u, w));
						G[v].insert(pii(u, y));
					}
					e[x][2] = y;
					break;
				//询问
				case 3 :
					res = bit.query(x, y); 
					for (int i = 1; i <= cnt_id; ++i) {  
						add(res, (trie.query(i, b[fid[i]], y + 1) - trie.query(i, b[fid[i]], x) + p) % p);  
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
