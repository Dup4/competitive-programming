#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
int n, m, k;
ll a, b, c;
map<int, ll> mp;

ll DFS(int x) {
    if (mp.find(x) != mp.end()) {
        return mp[x];
    } else if (x <= 0) {
        return 0;
    }
    ll res = INFLL;
    res = min(res, a + DFS(x - 2));
    res = min(res, b + DFS(x - 3));
    return mp[x] = res;
}

ll calc(int n) {
    ll res = 1ll * (n / 30) * min(a * 15, min(b * 10, (a + b) * 6));
    n %= 30;
    return res + DFS(n);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d%d%lld%lld%lld", &n, &m, &k, &a, &b, &c);
        mp.clear();
        ll res = INFLL;
        for (int i = 0; i <= k; ++i) {
            res = min(res, calc(n + i) + calc(m + i) + c * (k - i));
        }
        printf("%lld\n", res);
    }
    return 0;
}
