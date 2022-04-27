#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, x[N], a[N];
ll sum[N], cost[N];
ll T, L, R, need;
int u;

ll cost_l(int i) {
    //将L+1~i的物品移动到i的费用
    ll a = (sum[i] - sum[L]) * x[i] - (cost[i] - cost[L]);
    //将i+1~R的物品移动到i的费用
    ll b = (cost[R] - cost[i]) - x[i] * (sum[R] - sum[i]);
    //将多余的物品从R移动到i的费用
    ll c = (sum[R] - sum[L] - need) * (x[R] - x[i]);
    return a + b - c;
}

ll cost_r(int i) {
    //将L+1~i的物品移动到i的费用
    ll a = (sum[i] - sum[L]) * x[i] - (cost[i] - cost[L]);
    //将i+1~R的物品移动到i的费用
    ll b = (cost[R] - cost[i]) - x[i] * (sum[R] - sum[i]);
    //将多余的物品从L移动到i的费用
    ll c = (sum[R] - sum[L] - need) * (x[i] - x[L + 1]);
    return a + b - c;
}

bool check(ll x) {
    need = x;
    L = 0, R = 1, u = 0;
    while (1) {
        while (R < n && sum[R] - sum[L] < x) ++R;
        if (sum[R] - sum[L] < x)
            break;
        while (u < L) ++u;
        while (u < R && cost_l(u) > cost_l(u + 1)) ++u;
        if (cost_l(u) <= T)
            return 1;
        ++L;
    }
    L = n - 1, R = n, u = n;
    while (1) {
        while (L > 0 && sum[R] - sum[L] < x) --L;
        if (sum[R] - sum[L] < x)
            break;
        while (u > R) --u;
        while (u > L && cost_r(u) > cost_r(u - 1)) --u;
        if (cost_r(u) <= T)
            return 1;
        --R;
    }
    return 0;
}

int main() {
    while (scanf("%d%lld", &n, &T) != EOF) {
        T /= 2;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", x + i);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            sum[i] = sum[i - 1] + a[i];
            cost[i] = cost[i - 1] + 1ll * a[i] * x[i];
        }
        ll l = 0, r = sum[n], res = -1;
        while (r - l >= 0) {
            ll mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid + 1;
                res = mid;
            } else {
                r = mid - 1;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
