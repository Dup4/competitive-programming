#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], b[N];
int c[N], que[N * 4], l, r, res;

int solve1() {
    int tot = 0;
    memset(c, 0, sizeof c);
    l = 1, r = 0;
    for (int i = 1; i <= n; ++i) {
        ++c[a[i]];
        que[++r] = b[i];
    }
    bool F = 0;
    for (int i = 1; i <= n; ++i) {
        if (que[i] == 1) {
            for (int j = i + 1; j <= n; ++j) {
                if (que[j] != que[j - 1] + 1) {
                    return 1e9;
                }
            }
            F = 1;
            break;
        }
    }
    if (!F)
        return 1e9;
    for (int i = que[n] + 1; i <= n; ++i) {
        if (!c[i]) {
            return 1e9;
        }
        que[++r] = i;
        --c[i];
        ++c[que[l]];
        ++l;
        ++tot;
    }
    return tot;
}

bool check(int x) {
    int tot = 0;
    memset(c, 0, sizeof c);
    l = 1, r = 0;
    for (int i = 1; i <= n; ++i) {
        ++c[a[i]];
        que[++r] = b[i];
    }
    while (x--) {
        if (c[0] == 0) {
            break;
        }
        --c[0];
        que[++r] = 0;
        ++c[que[l]];
        ++l;
        ++tot;
    }
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 0) {
            return false;
        }
        --c[i];
        que[++r] = i;
        ++c[que[l]];
        ++l;
        ++tot;
    }
    res = min(res, tot);
    return true;
}

void solve2() {
    int l = 0, r = n;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", b + i);
        }
        res = solve1();
        solve2();
        printf("%d\n", res);
    }
    return 0;
}
