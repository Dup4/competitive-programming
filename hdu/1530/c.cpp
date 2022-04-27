#include <bits/stdc++.h>
using namespace std;
const int N = 310;
bool flag[N], a[N][N];
int ans, cnt[N], group[N], n, vis[N];
// 最大团： V中取K个顶点，两点间相互连接
// 最大独立集： V中取K个顶点，两点间不连接
// 最大团数量 = 补图中最大独立集数

bool dfs(int u, int pos) {
    int i, j;
    for (i = u + 1; i <= n; i++) {
        if (cnt[i] + pos <= ans)
            return 0;
        if (a[u][i]) {
            // 与目前团中元素比较，取 Non-N(i)
            for (j = 0; j < pos; j++)
                if (!a[i][vis[j]])
                    break;
            if (j == pos) {  // 若为空，则皆与 i 相邻，则此时将i加入到 最大团中
                vis[pos] = i;
                if (dfs(i, pos + 1))
                    return 1;
            }
        }
    }
    if (pos > ans) {
        for (i = 0; i < pos; i++) group[i] = vis[i];  // 最大团 元素
        ans = pos;
        return 1;
    }
    return 0;
}
void maxclique() {
    ans = -1;
    for (int i = n; i > 0; i--) {
        vis[0] = i;
        dfs(i, 1);
        cnt[i] = ans;
    }
}

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) scanf("%d", a[i] + j);
        maxclique();
        cout << ans << endl;
    }
    return 0;
}
