#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define N 100010
#define pii pair<int, int>
#define fi first
#define se second
const db eps = 1e-10;
int n, k;
pii a[N];

bool ok(db x) {
    vector<db> vec;
    for (int i = 1; i <= n; ++i) {
        vec.push_back(a[i].fi * (x - a[i].se));
    }
    sort(vec.begin(), vec.end());
    db tot = 0;
    for (int i = 0; i < n - k; ++i) {
        tot += vec[i];
    }
    return tot <= 0 || fabs(tot - 0) < eps;
}

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].fi);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i].se);
        }
        db l = 0, r = 1e3, res = 0;
        while (fabs(r - l) >= eps) {
            db mid = (l + r) / 2;
            if (ok(mid)) {
                l = mid;
                res = mid;
            } else {
                r = mid;
            }
        }
        printf("%.10f\n", res);
    }
    return 0;
}
