#include <bits/stdc++.h>

using namespace std;

long long di[20];
long long cnt[20];

long long gao(long long p) {
    int num[10] = {0}, f[20];
    long long ans = 0, t;
    int l;
    t = p;
    l = 0;
    while (t > 0) {
        t = t / 10;
        ++l;
    }
    t = p;
    for (int i = 1; i <= l; ++i) {
        f[l - i + 1] = t % 10;
        t = t / 10;
    }
    // printf("%d\n", l);
    for (int i = 1; i < l; ++i) {
        ++num[f[i]];
        ans += f[i] * di[l - i];
        for (int j = 0 + (i == 1); j < f[i]; ++j) ans += (l - i) * (9 - f[i]) * cnt[l - i - 1];
        for (int j = 0; j <= 9; ++j) ans += (l - i) * (9 - j) * num[j] * cnt[l - i - 1];
    }
    for (int i = 1; i <= f[l]; ++i)
        for (int j = 0; j < i; ++j) ans += num[j];
    for (int i = 2; i < l; ++i) ans += 36 * (i - 1) * cnt[i - 2];
    return ans - di[l - 1];
}

int main() {
    int T;
    di[1] = 0;
    cnt[0] = 1;
    cnt[1] = 10;
    for (int i = 2; i <= 14; ++i) {
        cnt[i] = cnt[i - 1] * 10;
        int t = (i - 1) * i / 2;
        di[i] = t * 45 * cnt[i - 2];
    }
    scanf("%d", &T);
    printf("  %lld\n", gao(100));
    while (T--) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", gao(y) - gao(x - 1));
    }
    return 0;
}
