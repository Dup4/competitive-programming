#include <cstdio>
#include <iostream>
using namespace std;
int S, D;
struct seg {
    int have[4005], all[4005];
    void change(int now, int l, int r, int lrange, int rrange, int v) {
        have[now] = max(have[now], v);
        if (lrange <= l && rrange >= r) {
            all[now] = max(all[now], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (lrange <= mid)
            change(now << 1, l, mid, lrange, rrange, v);
        if (rrange > mid)
            change(now << 1 | 1, mid + 1, r, lrange, rrange, v);
    }
    int qurry(int now, int l, int r, int lrange, int rrange) {
        if (lrange <= l && rrange >= r)
            return have[now];
        int mid = (l + r) >> 1, ans = all[now];
        if (lrange <= mid)
            ans = max(ans, qurry(now << 1, l, mid, lrange, rrange));
        if (rrange > mid)
            ans = max(ans, qurry(now << 1 | 1, mid + 1, r, lrange, rrange));
        return ans;
    }
};
struct sts {
    seg have[4005], all[4005];
    void Ch(int now, int l, int r, int lrange, int rrange, int L, int R, int v) {
        have[now].change(1, 1, S, L, R, v);
        if (lrange <= l && rrange >= r) {
            all[now].change(1, 1, S, L, R, v);
            return;
        }
        int mid = (l + r) >> 1;
        if (lrange <= mid)
            Ch(now << 1, l, mid, lrange, rrange, L, R, v);
        if (rrange > mid)
            Ch(now << 1 | 1, mid + 1, r, lrange, rrange, L, R, v);
    }
    int Qu(int now, int l, int r, int lrange, int rrange, int L, int R) {
        if (lrange <= l && rrange >= r)
            return have[now].qurry(1, 1, S, L, R);
        int mid = (l + r) >> 1, ans = all[now].qurry(1, 1, S, L, R);
        ;
        if (lrange <= mid)
            ans = max(ans, Qu(now << 1, l, mid, lrange, rrange, L, R));
        if (rrange > mid)
            ans = max(ans, Qu(now << 1 | 1, mid + 1, r, lrange, rrange, L, R));
        return ans;
    }
} t;
int main() {
    int n, d, s, w, x, y;
    scanf("%d%d%d", &D, &S, &n);
    D++;
    S++;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d%d", &d, &s, &w, &x, &y);
        int lj = t.Qu(1, 1, D, x + 1, x + d + 1, y + 1, y + s + 1);
        t.Ch(1, 1, D, x + 1, x + d + 1, y + 1, y + s + 1, lj + w);
    }
    printf("%d", t.Qu(1, 1, D, 1, D, 1, S));
}
