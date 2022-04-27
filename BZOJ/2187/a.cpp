#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a, b, c, d, x, y;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void sim(ll &a, ll &b) {
    ll t = gcd(a, b);
    a /= t;
    b /= t;
}

void gao(ll a, ll b, ll c, ll d, ll &x, ll &y) {
    sim(a, b);
    sim(c, d);
    ll nx = a / b + 1, ny = c / d + (c % d > 0) - 1;
    if (nx <= ny)
        x = nx, y = 1;
    else if (!a)
        x = 1, y = d / c + 1;
    else if (a < b && c <= d)
        gao(d, c, b, a, y, x);
    else
        gao(a % b, b, c - d * (a / b), d, x, y), x += y * (a / b);
}

int main() {
    while (~scanf("%lld%lld%lld%lld", &a, &b, &c, &d)) {
        gao(a, b, c, d, x, y);
        printf("%lld/%lld\n", x, y);
    }
    return 0;
}
