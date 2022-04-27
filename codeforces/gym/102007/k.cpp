#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int> > G;
vector<int> vec;

void gao(int u, int fa) {
    if (G[u].size() == 1) {
        vec.push_back(u);
        return;
    }
    for (auto &v : G[u])
        if (v != fa) {
            gao(v, u);
        }
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        G.clear();
        G.resize(n);
        vec.clear();
        for (int i = 1, u, v; i < n; ++i) {
            scanf("%d %d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        if (n == 2) {
            puts("1");
            puts("0 1");
            continue;
        }
        int rt = 0;
        for (int i = 0; i < n; ++i) {
            if (G[i].size() > 1) {
                rt = i;
                break;
            }
        }
        gao(rt, rt);
        int sze = vec.size();
        int cnt = (sze + 1) / 2;
        printf("%d\n", cnt);
        for (int i = 0; i + cnt < sze; ++i) {
            printf("%d %d\n", vec[i], vec[i + cnt]);
        }
        if (sze & 1) {
            if (vec[cnt - 1] != m) {
                printf("%d %d\n", vec[cnt - 1], m);
            } else {
                printf("%d %d\n", vec[cnt - 1], vec[cnt - 2]);
            }
        }
    }
    return 0;
}
