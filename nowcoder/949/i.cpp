#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
int n;
ll A, B;
const ll p = 1e9 + 7;
ll a[N][N], x[N];
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}
ll inv(ll a, ll p) {
    if (a == 1)
        return 1;
    return inv(p % a, p) * (p - p / a) % p;
}
int Gauss(int equ, int var) {
    int max_r, col, k;
    for (k = 0, col = 0; k < equ && col < var; ++k, ++col) {
        max_r = k;
        for (int i = k + 1; i < equ; ++i) {
            if (abs(a[i][col]) > abs(a[max_r][col])) {
                max_r = i;
            }
        }
        if (a[max_r][col] == 0) {
            --k;
            continue;
        }
        if (max_r != k) {
            for (int j = col; j < var + 1; ++j) {
                swap(a[k][j], a[max_r][j]);
            }
        }
        for (int i = k + 1; i < equ; ++i) {
            if (a[i][col] != 0) {
                ll LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                ll ta = LCM / abs(a[i][col]);
                ll tb = LCM / abs(a[k][col]);
                if (a[i][col] * a[k][col] < 0)
                    tb = -tb;
                for (int j = col; j < var + 1; ++j) {
                    a[i][j] = ((a[i][j] * ta - a[k][j] * tb) % p + p) % p;
                }
            }
        }
    }
    for (int i = k; i < equ; ++i) {
        if (a[i][col] != 0) {
            return -1;
        }
    }
    if (k < var)
        return var - k;
    for (int i = var - 1; i >= 0; --i) {
        ll tmp = a[i][var];
        for (int j = i + 1; j < var; ++j) {
            if (a[i][j] != 0) {
                tmp -= a[i][j] * x[j];
                tmp = (tmp % p + p) % p;
            }
        }
        x[i] = (tmp * inv(a[i][i], p)) % p;
    }
    return 0;
}

int main() {
    while (scanf("%d%lld%lld", &n, &A, &B) != EOF) {
        memset(a, 0, sizeof a);
        a[0][0] = p - A;
        a[0][1] = A;
        a[0][n] = -1;
        for (int i = 2; i < n; ++i) {
            a[i - 1][i - 2] = (1 - A - B + 2ll * p) % p;
            a[i - 1][i - 1] = (B - 1 + p) % p;
            a[i - 1][i] = A;
            a[i - 1][n] = -1;
        }
        a[n - 1][n - 1] = 1;
        Gauss(n, n);
        printf("%lld\n", x[0]);
    }
    return 0;
}
