#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e5 + 10;
ll f[N];
int c[5], d[5], s, T;

int main() {
    for (int i = 0; i < 4; ++i) scanf("%d", c + i);
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j <= 100000 - c[i]; ++j) {
            f[j + c[i]] += f[j];
        }
    }
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 4; ++i) scanf("%d", d + i);
        scanf("%d", &s);
        ll res = 0;
        for (int i = 0; i < 16; ++i) {
            int op = 0;
            ll sum = 0;
            for (int j = 0; j < 4; ++j) {
                if ((i >> j) & 1) {
                    sum += 1ll * c[j] * (d[j] + 1);
                    op ^= 1;
                }
            }
            if (sum > s)
                continue;
            res += f[s - sum] * (op ? -1 : 1);
        }
        printf("%lld\n", res);
    }
    return 0;
}
