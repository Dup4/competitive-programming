#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int N = 1e6 + 10;
int n;
ll a, b, c, x[N];

namespace DP {
ll f[N], y[N];
int que[N], head, tail;
db slope(int i, int j) {
    return (y[i] - y[j]) * 1.0 / (x[i] - x[j]);
}
void gao() {
    memset(f, 0, sizeof f);
    head = 1, tail = 0;
    que[++tail] = 0;
    for (int i = 1; i <= n; ++i) {
        while (head < tail && slope(que[head], que[head + 1]) >= x[i] * a * 2) ++head;
        f[i] = f[que[head]] + a * (x[i] - x[que[head]]) * (x[i] - x[que[head]]) + b * (x[i] - x[que[head]]) + c;
        y[i] = f[i] + a * x[i] * x[i] - b * x[i];
        while (head < tail && slope(que[tail - 1], que[tail]) <= slope(que[tail], i)) --tail;
        que[++tail] = i;
    }
    printf("%lld\n", f[n]);
}
}  // namespace DP

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%lld%lld%lld", &a, &b, &c);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", x + i);
            x[i] += x[i - 1];
        }
        DP::gao();
    }
    return 0;
}
