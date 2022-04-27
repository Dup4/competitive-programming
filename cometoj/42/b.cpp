#include <bits/stdc++.h>
using namespace std;

#define N 20
int n, a[N];

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

bool check(int x) {
    for (int i = 0; i < n; ++i)
        if ((x >> i) & 1) {
            for (int j = 0; j < i; ++j)
                if ((x >> j) & 1) {
                    if (gcd(a[i + 1], a[j + 1]) != 1) {
                        return false;
                    }
                }
        }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        int res = 1;
        for (int i = 0; i < (1 << n); ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                cnt += (i >> j) & 1;
            }
            if (check(i)) {
                res = max(res, cnt);
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
