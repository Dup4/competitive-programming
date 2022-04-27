#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll d, x, y;

//求出p2 - D * q2 = 1的基解(
bool PQA(ll D, ll &p, ll &q) {
    ll d = sqrt(D);
    for (ll i = d - 1; i <= d + 1; ++i)
        if (i * i == D)
            return false;
    ll u = 0, v = 1, a = int(sqrt(D)), a0 = a, lastp = 1, lastq = 0;
    p = a, q = 1;
    do {
        u = a * v - u;
        v = (D - u * u) / v;
        a = (a0 + u) / v;
        ll thisp = p, thisq = q;
        p = a * p + lastp;
        q = a * q + lastq;
        lastp = thisp;
        lastq = thisq;
    } while ((v != 1 && a <= a0));
    p = lastp;
    q = lastq;
    if (p * p - D * q * q == -1) {
        p = lastp * lastp + D * lastq * lastq;
        q = 2 * lastp * lastq;
    }
    return true;
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%lld", &d);
        assert(PQA(d, x, y));
        printf("%lld %lld\n", x, y);
    }
    return 0;
}
