#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define INF 0x3f3f3f3f
const int p = 43200;
int n, a[N], now, Min, Max;

int f(int Min, int Max, int now) {
    if (now <= Min)
        return Max - now;
    if (now >= Max)
        return now - Min;
    return (Max - Min) + min(now - Min, Max - now);
}

int solve(int now) {
    int res = 1e9;
    for (int l = 1, r = 1; r < p * 2; ++r) {
        while (l < r && a[r] - a[l] >= n) {
            ++l;
        }
        if (a[r] - a[l - 1] == n) {
            res = min(res, f(l, r, now));
        }
    }
    return res;
}

int get() {
    int h, m, s;
    scanf("%d%d%d", &h, &m, &s);
    h %= 12;
    return (h * 3600 + m * 60 + s);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(a, 0, sizeof a);
        now = get();
        for (int i = 1; i <= n; ++i) {
            int t = get();
            ++a[t];
            ++a[t + p];
        }
        for (int i = 1; i < p * 2; ++i) {
            a[i] += a[i - 1];
        }
        printf("%d.00\n", min(solve(now), solve(now + p)) * 6);
    }
    return 0;
}
