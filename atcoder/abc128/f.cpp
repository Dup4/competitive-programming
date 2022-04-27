#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, a[N];
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

ll f(int A, int B) {
    int G = gcd(A, B);
    if (A / G == B / G + 1) {
        return 0;
    }
    ll res = 0;
    int now = 0;
    while (1) {
        now += A;
        res += a[now];
        if (now == n - 1) {
            return res;
        }
        now -= B;
        res += a[now];
        if (now == n - 1) {
            return res;
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", a + i);
        }
        ll res = 0;
        for (int A = 1; A < n - 1; ++A) {
            int m = n - 1 - A;
            for (int i = 1; 1ll * i * i <= m; ++i) {
                if (m % i == 0) {
                    int x = i, y = m / i;
                    if (x < A) {
                        res = max(res, f(A, A - x));
                    }
                    if (y < A && x != y) {
                        res = max(res, f(A, A - y));
                    }
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
