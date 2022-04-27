#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
inline int read() {
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
int n, P;
ll fac[N];
ll Pow(ll a, int b, int P) {
    ll re = 1;
    for (; b; b >>= 1, a = a * a % P)
        if (b & 1)
            re = re * a % P;
    return re;
}
void iniFac(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
}
ll C(int n, int m) {
    return fac[n] * Pow(fac[m] * fac[n - m] % P, P - 2, P) % P;
}
ll Lucas(int n, int m) {
    if (n < m)
        return 0;
    ll re = 1;
    for (; m; m /= P, n /= P) re = re * C(n % P, m % P) % P;
    return re;
}
int size[N << 1];
ll f[N << 1];
void dp() {
    for (int i = n; i >= 1; i--) {
        int l = i << 1, r = i << 1 | 1;
        size[i] = size[l] + size[r] + 1;
        f[i] = Lucas(size[i] - 1, size[l]) * (l > n ? 1 : f[l]) % P * (r > n ? 1 : f[r]) % P;
    }
    printf("%lld", f[1]);
}
int main() {
    n = read();
    P = read();
    iniFac(n);
    dp();
}
