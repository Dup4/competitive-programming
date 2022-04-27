#include <bits/stdc++.h>
using namespace std;

#define N 510
#define pii pair<int, int>
#define fi first
#define se second
int n, m, a[N][N];
vector<vector<pii>> vec[2];
int del[N];

bool ok(int x) {
    vec[0].clear();
    vec[0].resize(m + 1);
    vec[1].clear();
    vec[1].resize(m + 1);
    for (int i = 1; i <= n; ++i) {
        vec[1][a[i][1]].push_back(pii(i, 1));
    }
    for (int j = 1; j <= m; ++j) del[j] = 0;
    for (int i = 1;; ++i) {
        int now = i & 1;
        bool F = 1;
        for (int j = 1; j <= m; ++j) {
            int sze = (int)vec[now][j].size();
            if (sze > x) {
                F = 0;
                del[j] = 1;
            }
        }
        if (F)
            return 1;
        for (int j = 1; j <= m; ++j) {
            for (auto it : vec[now][j]) {
                while (it.se <= m && del[a[it.fi][it.se]]) ++it.se;
                if (it.se > m)
                    return 0;
                vec[now ^ 1][a[it.fi][it.se]].push_back(it);
            }
            vec[now][j].clear();
        }
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        int l = 1, r = n, res = -1;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (ok(mid)) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
