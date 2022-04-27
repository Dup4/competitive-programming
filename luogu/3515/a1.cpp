#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, a[N];
double ans[N];

namespace DP {
int bound[N], que[N], head, tail;
double sqr[N];
void init() {
    for (int i = 0; i < N; ++i) sqr[i] = sqrt(i);
}
inline double calc(int i, int j) {
    return 1. * a[j] + sqr[i - j];
}
int getBound(int x, int y) {
    int l = y, r = bound[x] == -1 ? n : bound[x];
    int res = r + 1;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(mid, x) <= calc(mid, y)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res;
}
void gao() {
    memset(bound, -1, sizeof bound);
    head = 1, tail = 0;
    for (int i = 1; i <= n; ++i) {
        while (head < tail && calc(bound[tail - 1], que[tail]) < calc(bound[tail - 1], i)) --tail;
        bound[tail] = getBound(que[tail], i);
        que[++tail] = i;
        while (head < tail && bound[head] <= i) ++head;
        ans[i] = max(ans[i], calc(i, que[head]));
    }
}
}  // namespace DP

int main() {
    DP::init();
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        memset(ans, 0, sizeof ans);
        DP::gao();
        reverse(a + 1, a + 1 + n);
        reverse(ans + 1, ans + 1 + n);
        DP::gao();
        for (int i = n; i >= 1; --i) printf("%d\n", max((int)ceil(ans[i]) - a[i], 0));
    }
    return 0;
}
