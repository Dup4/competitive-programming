#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n, x[N], a[N], b[N];
ll T;

int main() {
    while (scanf("%d%lld", &n, &T) != EOF) {
        T /= 2;
        memset(b, 0, sizeof b);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", x + i);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        if (n == 1) {
            printf("%d\n", a[1]);
            continue;
        }
        // num[0] 表示左边的个数，num[1]表示右边的个数
        vector<ll> num(2, 0);
        ll res = 0, fee = 0;
        int l = 1, r = 2;
        //处理刚开始的情况
        while (r <= n) {
            ll dis = (x[r] - x[1]);
            ll need = dis * (a[r] - b[r]);
            if (fee + need <= T) {
                fee += need;
                b[r] = a[r];
                num[1] += b[r];
                ++r;
            } else {
                ll add = (T - fee) / dis;
                b[r] += add;
                fee += dis * add;
                num[1] += add;
                break;
            }
        }
        for (int i = 1; i <= n; ++i) {
            res = max(res, num[0] + num[1] + a[i]);
            if (i < n) {
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
