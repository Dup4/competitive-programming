#include <bits/stdc++.h>
using namespace std;

#define ll long long
int m, q;
ll k, x;

int main() {
    while (scanf("%d%lld%d", &m, &k, &q) != EOF) {
        if (m == 1) {
            set<ll> s;
            int op;
            ll x;
            while (q--) {
                scanf("%d%lld", &op, &x);
                switch (op) {
                    case 1:
                        s.insert(x);
                        break;
                    case 2:
                        s.erase(x);
                        break;
                    default:
                        assert(0);
                }
                ll res = k;
                if (!s.empty()) {
                    res = *s.begin();
                }
                printf("%lld\n", res);
            }
        } else {
            ll tot = 0;
            ll base = 1;
            for (int i = 1; i <= k; ++i) {
                tot += base;
                base <<= 1;
            }
            int op;
            ll x;
            set<ll> s;
            while (q--) {
                scanf("%d%lld", &op, &x);
                switch (op) {
                    case 1:
                        s.insert(x);
                        break;
                    case 2:
                        s.erase(x);
                        break;
                    default:
                        assert(0);
                }
                ll res = tot;
                for (auto i : s) {
                    ll u = i;
                    int dep = 1;
                    bool F = 1;
                    while (u) {
                        u = (u - 1) / 2;
                        ++dep;
                        if (s.find(u) != s.end()) {
                            F = 0;
                            break;
                        }
                    }
                    if (F) {
                        // cout << i << " " << dep << endl;
                        base = 1;
                        ll tmp = 0;
                        for (int i = dep; i <= k; ++i) {
                            tmp += base;
                            base <<= 1;
                        }
                        res -= tmp;
                    }
                }
                printf("%lld\n", res);
            }
        }
    }
    return 0;
}
