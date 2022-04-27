#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 200010
int n, m, a[N];

struct SEG {
    int a[N << 2];
    void init() {
        memset(a, -1, sizeof a);
    }
    void update(int id, int l, int r, int x, int v) {
        if (l == r) {
            a[id] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(id << 1, l, mid, x, v);
        else
            update(id << 1 | 1, mid + 1, r, x, v);
        a[id] = min(a[id << 1], a[id << 1 | 1]);
    }
} seg;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        seg.init();
        int res = INF;
        for (int i = 1; i <= n; ++i) {
            seg.update(1, 1, m, a[i], i);
            int t = seg.a[1];
            if (t != -1) {
                res = min(res, i - t + 1);
            }
        }
        if (res == INF) {
            puts("NO");
            return 0;
        }
        printf("%d\n", res);
    }
    return 0;
}
