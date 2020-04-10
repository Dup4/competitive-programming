#include <bits/stdc++.h>
const int N = 4e3 + 10;
using namespace std;
int n, m;

struct Graph {
	struct E { int to, nx, w; }e[N << 1]; int h[N], cnt;
	void init(int n) { for (int i = 0; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v, int w = 0) { e[++cnt] = { v, h[u], w}; h[u] = cnt; } 
}G;

struct Node{
    int fa, val, depth;
    vector<int> ch;
} node[MAXM];



int n, m, S, T, B, ans, tclock = 0;
vector<int> G[N];
Edge edge[MAXM];
int d[N];

inline void addEdge(int u, int v, int w) {
    edge[B].u = u;
    edge[B].v = v;
    edge[B].w = w;
    G[u].push_back(B ++);
}

inline void Change(int x, int val) {
    node[x].val = val;
    for(int i = 0;i < node[x].ch.size();i ++) {
        node[node[x].ch[i]].val = val;
        Change(node[x].ch[i], val);
    }
}

inline void Maintain(int x) {
    for(int i = 0;i < node[x].ch.size();i ++) {
        node[node[x].ch[i]].depth = node[x].depth + 1;
        Maintain(node[x].ch[i]);
    }
}

inline int Query(int x) {
    return node[x].val;
}

inline void Link(int x, int y) {
    node[x].fa = y;
    node[x].depth = node[y].depth + 1;
    Maintain(x);
    node[y].ch.push_back(x);
}

inline void Cut(int x) {
    Node &s = node[node[x].fa];
    node[x].depth = 1;
    Maintain(x);
    for(int i = 0;i < s.ch.size();i ++) {
        if(s.ch[i] == x) {
            for(int j = i;j < s.ch.size() - 1;j ++) {
                s.ch[j] = s.ch[j + 1];
            }
            s.ch.pop_back();
            break;
        }
    }
    node[x].fa = 0;
}

inline int lca(int x, int y) {
    if(x == y) return x;
    if(node[x].depth < node[y].depth) swap(x, y);
    for(;node[x].depth == node[y].depth;) x = node[x].fa;
    for(;x == y;x = node[x].fa, y = node[y].fa);
    return x;
}

inline bool SPFA() {
    int i, j, x, cnt = 0;
    queue<int> Q;
    memset(d, 0x3f, sizeof(d));
    d[S] = 0;
    node[S].depth = 1;
    Q.push(S);
    Change(S, 1);
    while(!Q.empty()) {
        x = Q.front();
        Q.pop(); 
        cnt ++;
        if(!Query(x)) continue;
        for(i = 0;i < G[x].size();i ++) {
            Edge &e = edge[G[x][i]];
            //cout << G[x][i] << endl;
            //cout << d[x] << ' ' << e.w << ' ' << d[e.v] << ' ' << x << ' ' << e.v << endl;
            if(d[x] + e.w < d[e.v]) {
                if(lca(x, e.v) == e.v) {
                    return 0;
                }
                d[e.v] = d[x] + e.w;
                Q.push(e.v);
                Change(e.v, 0);
                node[e.v].val = 1;
                Cut(e.v);
                Link(e.v, x);
            }
        }
    }
    return 1;
}

int main() {
	int _T; scanf("%d", &_T);
    while (_T--) {
		scanf("%d%d", &n, &m);
		SPFA::init(n);
		S = 4009;
		for (int i = 1; i <= n; ++i)
			G.addEdge(S, i, 0);
		for (int i = 1, u, v, w; i <= m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			
		}
	    int i, a, b, c;
	    readInt(n);
	    readInt(m);
	    B = 0;
	    for(i = 1;i <= n;i ++) {
	        G[i].clear();
	        node[i].ch.clear();
	        node[i].depth = 0;
	        node[i].fa = 0;
	        node[i].val = 0;
	    }
	    S = 4009;
	    for(i = 1;i <= n;i ++) {
	        addEdge(S, i, 0);
	    }
	    for(i = 0;i < m;i ++) {
	        readInt(a);
	        readInt(b);
	        readInt(c);
	        addEdge(a, b, c);
	    }
			
	}
    return 0;
}
