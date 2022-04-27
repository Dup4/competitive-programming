#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 6e2 + 10;
const int INF = 0x3f3f3f3f;
int n, m;

struct StoerWagner {
    int mat[N][N], dis[N], v[N];
    bool vis[N];
    void init() {
        memset(mat, 0, sizeof mat);
    }
    int gao() {
        int res = INF;
        for (int i = 0; i < n; ++i) v[i] = i + 1;  //初始化第i个结点就是i
        while (n > 1) {
            int maxp = 1, prev = 0;
            for (int i = 1; i < n; ++i) {  //初始化到已圈集合的割大小,并找出最大距离的顶点
                dis[v[i]] = mat[v[0]][v[i]];
                if (dis[v[i]] > dis[v[maxp]])
                    maxp = i;
            }
            memset(vis, 0, sizeof(vis));
            vis[v[0]] = true;
            for (int i = 1; i < n; ++i) {
                if (i == n - 1) {  //只剩最后一个没加入集合的点，更新最小割
                    res = min(res, dis[v[maxp]]);
                    for (int j = 0; j < n; ++j) {  //合并最后一个点以及推出它的集合中的点
                        mat[v[prev]][v[j]] += mat[v[j]][v[maxp]];
                        mat[v[j]][v[prev]] = mat[v[prev]][v[j]];
                    }
                    v[maxp] = v[--n];  //第maxp个节点去掉，第n个节点变成第maxp个
                }
                vis[v[maxp]] = true;
                prev = maxp;
                maxp = -1;
                for (int j = 1; j < n; ++j)
                    if (!vis[v[j]]) {  //将上次求的maxp加入集合，合并与它相邻的边到割集
                        dis[v[j]] += mat[v[prev]][v[j]];
                        if (maxp == -1 || dis[v[maxp]] < dis[v[j]])
                            maxp = j;
                    }
            }
        }
        return res;
    }
} sw;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        sw.init();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            sw.mat[u][v] += w;
            sw.mat[v][u] += w;
        }
        printf("%d\n", sw.gao());
    }
    return 0;
}
