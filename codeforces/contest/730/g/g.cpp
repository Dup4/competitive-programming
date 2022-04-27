#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pLL = pair<ll, ll>;
#define fi first
#define se second
const int N = 210;
int n;
ll s[N], d[N];

vector<pLL> vec;

bool cross(pLL x, pLL y) {
    if ((x.fi <= y.fi && x.se >= y.fi) || (x.fi <= y.se && x.se >= y.se) || (y.fi <= x.fi && y.se >= x.fi) ||
            (y.fi <= x.se && y.fi >= x.se))
        return true;
    return false;
}

bool ok(ll l, ll r) {
    for (auto &it : vec) {
        if (cross(pLL(l, r), it)) {
            return false;
        }
    }
    return true;
}

pLL get(ll d) {
    if (ok(1, 1 + d - 1))
        return pLL(1, 1 + d - 1);
    for (auto &it : vec) {
        if (ok(it.se + 1, it.se + d)) {
            return pLL(it.se + 1, it.se + d);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", s + i, d + i);
    }
    for (int i = 1; i <= n; ++i) {
        pLL tmp = pLL(s[i], s[i] + d[i] - 1);
        if (!ok(s[i], s[i] + d[i] - 1)) {
            tmp = get(d[i]);
        }
        vec.push_back(tmp);
        sort(vec.begin(), vec.end());
        printf("%lld %lld\n", tmp.fi, tmp.se);
    }
    return 0;
}
