#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
struct Hash {
    vector<int> a;
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;
struct E {
    int u, v;
    E() {}
    E(int u, int v) : u(u), v(v) {}
} e[N];
int n, m, d[N], fa[N], id[N], vis[N];
int find(int x) {
    return fa[x] == 0 ? x : fa[x] = find(fa[x]);
}
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v)
        fa[u] = v;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        hs.init();
        for (int i = 1, u, v; i <= n; ++i) {
            scanf("%d%d", &u, &v);
            hs.add(u);
            hs.add(v);
            e[i] = E(u, v);
        }
        hs.gao();
        m = hs.a.size();
        for (int i = 1; i <= m; ++i) {
            d[i] = fa[i] = 0;
            id[i] = 0;
            vis[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            e[i].u = hs.get(e[i].u);
            e[i].v = hs.get(e[i].v);
            ++d[e[i].u];
            ++d[e[i].v];
            merge(e[i].u, e[i].v);
        }
        int rt = 1, frt = find(rt);
        for (int i = 1; i <= n; ++i) {
            int &u = e[i].u, &v = e[i].v;
            if (d[u] > d[v])
                swap(u, v);
            int fu = find(u);
            if (fu == frt)
                continue;
            if (id[fu] == 0) {
                id[fu] = i;
            } else if (d[v] > d[e[id[fu]].v]) {
                id[fu] = i;
            }
            if (vis[fu] == 0 && d[u] == 1) {
                vis[fu] = i;
            }
        }
        vector<int> vec;
        for (int i = 1; i <= m; ++i) {
            int fi = find(i);
            if (fi != i || fi == frt)
                continue;
            if (vis[i])
                vec.push_back(vis[i]);
            else
                vec.push_back(id[i]);
        }
        int sze = vec.size();
        printf("%d\n", sze);
        for (int i = 0; i < sze; ++i) {
            //	assert(vec[i] && e[vec[i]].v != 1);
            int u = -1;
            if (d[e[vec[i]].u] == 1) {
                u = e[vec[i]].u;
            } else {
                u = e[vec[i]].v;
            }
            printf("%d %d %d\n", vec[i], hs.a[u - 1], hs.a[0]);
        }
        //	for (int i = 1;  i <= m; ++i) fa[i] = 0, d[i] = 0;
        //    for (int i = 1; i <= n; ++i) {
        //		int u = e[i].u, v = e[i].v;
        //		++d[u]; ++d[v];
        //		merge(u, v);
        //	}
        //	for (int i = 1; i <= m; ++i) {
        //		if (d[i] && find(i) != find(1))
        //		   assert(0);
        //	}
    }
    return 0;
}
