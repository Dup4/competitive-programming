#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 u128;
using namespace std;
const int N = 1e7 + 5;

namespace DIVCNT {
struct point {
    ll x, y;
    point(ll _x = 0, ll _y = 0) {
        x = _x;
        y = _y;
    }
    point operator+(const point &t) const {
        return point(x + t.x, y + t.y);
    }
} st[N], L, R, M;
ll n;
inline bool inR(ll x, ll y) {
    return x * y <= n;
}
inline double slope(ll x) {
    return (double)n / x / x;
}
inline u128 gao(ll _n) {
    n = _n;
    u128 ret = 0;
    int t = 0, rt = cbrt(n);
    st[++t] = point(1, 0);
    st[++t] = point(1, 1);
    ll m = sqrt(n), x = n / m, y = m + 1;
    while (1) {
        for (L = st[t--]; !inR(x + L.x, y - L.y); x += L.x, y -= L.y) ret += x * L.y + (L.y + 1) * (L.x - 1) / 2;
        if (y <= rt)
            break;
        for (R = st[t]; inR(x + R.x, y - R.y); R = st[--t]) L = R;
        while (1) {
            M = L + R;
            if (!inR(x + M.x, y - M.y))
                st[++t] = (R = M);
            else {
                if (slope(x + M.x) <= (double)R.y / R.x)
                    break;
                L = M;
            }
        }
    }
    for (int i = 1; i < y; i++) ret += n / i;
    return ret * 2 - 1ll * m * m;
}
};  // namespace DIVCNT

inline void write(u128 x) {
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

inline void writeln(const u128 &x) {
    write(x);
    putchar('\n');
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        ll n;
        scanf("%lld", &n);
        writeln(DIVCNT::gao(n));
    }
    return 0;
}
