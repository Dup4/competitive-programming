#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N];
multiset<int> se;
vector<vector<int> > vec;

void solve() {
    int fail = n + 1;
    for (int i = 1; i <= n; ++i) {
        auto pos = se.begin();
        if (*pos != a[i]) {
            b[i] = *pos;
            se.erase(pos);
            continue;
        } else {
            pos = se.upper_bound(*pos);
            if (pos != se.end()) {
                b[i] = *pos;
                se.erase(pos);
                continue;
            }
        }
        pos = se.begin();
        fail = min(fail, i - 1);
        for (; fail >= 1; --fail) {
            if (b[fail] != *pos && a[fail] != *pos) {
                b[i] = b[fail];
                b[fail] = *pos;
                se.erase(pos);
                --fail;
                break;
            }
        }
        if (b[i] == -1) {
            break;
        }
    }
    if (b[n] == -1) {
        puts("Impossible");
        return;
    }
    for (int i = 1; i <= n; ++i) {
        vec[a[i]].push_back(b[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!vec[i].empty()) {
            sort(vec[i].begin(), vec[i].end(), [&](int x, int y) {
                return x > y;
            });
        }
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", vec[a[i]].back(), " \n"[i == n]);
        vec[a[i]].pop_back();
    }
}

void init() {
    se.clear();
    for (int i = 1; i <= n; ++i) {
        b[i] = -1;
    }
    vec.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        vec[i].clear();
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            se.insert(a[i]);
        }
        solve();
    }
    return 0;
}
