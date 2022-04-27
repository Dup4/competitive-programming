#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
const ll p = 998244353;
int n, len, inv2;
int a[N], b[N], c[N], d[N];

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

// 1 FWT
// -1 IFWT
void FWT_or(int *a, int opt) {
    for (int i = 1; i < len; i <<= 1) {
        for (int o = i << 1, j = 0; j < len; j += o) {
            for (int k = 0; k < i; ++k) {
                if (opt == 1) {
                    a[i + j + k] = (a[j + k] + a[i + j + k]) % p;
                } else {
                    a[i + j + k] = (a[i + j + k] + p - a[j + k]) % p;
                }
            }
        }
    }
}

void FWT_and(int *a, int opt) {
    for (int i = 1; i < len; i <<= 1) {
        for (int o = i << 1, j = 0; j < len; j += o) {
            for (int k = 0; k < i; ++k) {
                if (opt == 1) {
                    a[j + k] = (a[j + k] + a[i + j + k]) % p;
                } else {
                    a[j + k] = (a[j + k] + p - a[i + j + k]) % p;
                }
            }
        }
    }
}

void FWT_xor(int *a, int opt) {
    for (int i = 1; i < len; i <<= 1) {
        for (int o = i << 1, j = 0; j < len; j += o) {
            for (int k = 0; k < i; ++k) {
                int X = a[j + k], Y = a[i + j + k];
                a[j + k] = (X + Y) % p;
                a[i + j + k] = (X + p - Y) % p;
                if (opt == -1) {
                    a[j + k] = 1ll * a[j + k] * inv2 % p;
                    a[i + j + k] = 1ll * a[i + j + k] * inv2 % p;
                }
            }
        }
    }
}

void Copy(int *a, int *b) {
    for (int i = 0; i < len; ++i) a[i] = b[i];
}

int main() {
    inv2 = qmod(2, p - 2);
    while (scanf("%d", &n) != EOF) {
        len = 1 << n;
        for (int i = 0; i < len; ++i) scanf("%d", a + i);
        for (int i = 0; i < len; ++i) scanf("%d", b + i);

        // or
        Copy(c, a);
        Copy(d, b);
        FWT_or(c, 1);
        FWT_or(d, 1);
        for (int i = 0; i < len; ++i) c[i] = 1ll * c[i] * d[i] % p;
        FWT_or(c, -1);
        for (int i = 0; i < len; ++i) printf("%d%c", c[i], " \n"[i == len - 1]);

        // and
        Copy(c, a);
        Copy(d, b);
        FWT_and(c, 1);
        FWT_and(d, 1);
        for (int i = 0; i < len; ++i) c[i] = 1ll * c[i] * d[i] % p;
        FWT_and(c, -1);
        for (int i = 0; i < len; ++i) printf("%d%c", c[i], " \n"[i == len - 1]);

        // xor

        Copy(c, a);
        Copy(d, b);
        FWT_xor(c, 1);
        FWT_xor(d, 1);
        for (int i = 0; i < len; ++i) c[i] = 1ll * c[i] * d[i] % p;
        FWT_xor(c, -1);
        for (int i = 0; i < len; ++i) printf("%d%c", c[i], " \n"[i == len - 1]);
    }
    return 0;
}
