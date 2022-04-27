#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}

const ll INF = 1e18;

ll f, T, t0, a1, t1, p1, a2, p2, t2;

inline ll ceil(ll x, ll y) {
    return (x + y - 1) / y;
}

inline void chmin(ll &x, ll y) {
    if (x > y)
        x = y;
}

struct E {
    ll a, t, p;
    bool operator<(const E &other) const {
        if (t != other.t)
            return t < other.t;
        return p < other.p;
    }
} e[3];

ll calc(ll remind, ll x, E e) {
    ll _remind = remind - e.a * x;
    if (_remind < 0)
        _remind = 0;
    ll useT = e.t * (remind - _remind);
    return useT + _remind * t0;
}

ll gao() {
    if (t0 * f <= T)
        return 0;
    ll res = INF;
    int n = ceil(f, e[1].a);
    for (int i = 0; i <= n; ++i) {
        ll now = e[1].p * i;
        ll remind = f - e[1].a * i;
        if (remind < 0)
            remind = 0;
        ll useT = e[1].t * (f - remind);
        if (useT > T)
            break;
        ll _T = T - useT;
        //	dbg(i, remind, f - remind, useT, now, _T);
        if (remind * e[0].t <= _T) {
            chmin(res, now);
            //	dbg(i, remind, remind * e[0].t, now);
        } else {
            if (remind * e[2].t > _T)
                continue;
            int _n = ceil(remind, e[2].a);
            int l = 0, r = _n, tar = _n;
            while (r - l >= 0) {
                int mid = (l + r) >> 1;
                //	dbg(mid, calc(remind, mid, e[2]));
                if (calc(remind, mid, e[2]) <= _T) {
                    tar = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            //	dbg(i, tar, _n);
            chmin(res, now + e[2].p * tar);
        }
    }
    if (res >= INF)
        return -1;
    return res;
}

int main() {
    scanf("%lld%lld%lld", &f, &T, &t0);
    scanf("%lld%lld%lld", &a1, &t1, &p1);
    scanf("%lld%lld%lld", &a2, &t2, &p2);
    e[0] = {1, t0, 0};
    e[1] = {a1, t1, p1};
    e[2] = {a2, t2, p2};
    sort(e + 1, e + 3);
    printf("%lld\n", gao());
    return 0;
}
