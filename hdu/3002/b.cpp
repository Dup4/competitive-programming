#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e2 + 10;
int n, m;

struct StoerWagner {
    int mat[N][N], weight[N];
    int del[N], vis[N];
    void init() {
        memset(mat, 0, sizeof mat);
        memset(del, 0, sizeof del);
    }
    int work(int &s, int &t, int cnt) {
        memset(weight, 0, sizeof weight);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++i) {
            if (!del[i]) {
                t = i;
                break;
            }
        }
        while (--cnt) {
            vis[s = t] = true;
            for (int i = 1; i <= n; ++i)
                if (!del[i] && !vis[i]) {
                    weight[i] += mat[s][i];
                }
            t = 0;
            for (int i = 1; i <= n; ++i)
                if (!del[i] && !vis[i]) {
                    if (weight[i] >= weight[t])
                        t = i;
                }
        }
        return weight[t];
    }
    void merge(int s, int t) {
        for (int i = 1; i <= n; ++i) {
            mat[s][i] += mat[t][i];
            mat[i][s] += mat[i][t];
        }
        del[t] = true;
    }
    int gao() {
        int res = 1e9;
        int s, t;
        for (int i = n; i > 1; --i) {
            res = min(res, work(s, t, i));
            cout << s << " " << t << endl;
            merge(s, t);
        }
        return res;
    }
} sw;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        sw.init();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ++u, ++v;
            sw.mat[u][v] += w;
            sw.mat[v][u] += w;
        }
        printf("%d\n", sw.gao());
    }
    return 0;
}
