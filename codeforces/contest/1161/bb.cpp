#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define pii pair<int, int>
#define fi first
#define se second
int n, m;
pii a[N];
set<pii> se;

bool check(int x) {
    if (x == n) {
        return false;
    }
    for (int i = 1; i <= m; ++i) {
        pii o, p;
        o.fi = (a[i].fi + x) % n;
        o.se = (a[i].se + x) % n;
        p = o;
        swap(p.fi, p.se);
        auto pos = se.lower_bound(o), pos2 = se.lower_bound(p);
        if ((pos == se.end() || (*pos).fi != o.fi || (*pos).se != o.se) &&
                (pos2 == se.end() || (*pos2).fi != p.fi || (*pos2).se != p.se)) {
            return false;
        }
    }
    return true;
}

void solve() {
    for (int i = 1; i * i <= n; ++i)
        if (n % i == 0) {
            if (check(i) || check(n / i)) {
                puts("Yes");
                return;
            }
        }
    puts("No");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        se.clear();
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &a[i].fi, &a[i].se);
            --a[i].fi;
            --a[i].se;
            se.insert(a[i]);
        }
        solve();
    }
    return 0;
}
