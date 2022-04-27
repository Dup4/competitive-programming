#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
int n, k;
ll s, m;
bool vis[N];
int arr[N];
vector<ll> vec;
ll sum[N];
int ql, qr, que[N];

ll get(vector<ll> &v, int limit) {
    ql = 1, qr = 0;
    ll res = 0;
    for (int i = 0, sze = v.size(); i < sze; ++i) {
        sum[i] = v[i] + (i ? sum[i - 1] : 0);
        if (i < limit)
            res = max(res, sum[i]);
        while (ql <= qr && que[ql] + limit < i) ++ql;
        if (ql <= qr)
            res = max(res, sum[i] - sum[que[ql]]);
        while (ql <= qr && sum[que[qr]] >= sum[i]) --qr;
        que[++qr] = i;
    }
    return res;
}

ll work(vector<ll> &v) {
    int sze = v.size();
    ll S = 0;
    for (int i = 0; i < sze; ++i) S += v[i];
    S = max(0ll, S);
    int t = m / sze, remind = m % sze;
    for (int i = 0; i < sze; ++i) v.push_back(v[i]);
    ll ans1 = get(v, sze);
    ll ans2 = get(v, remind);
    if (t == 0)
        return ans2;
    ans1 += (t ? 1ll * (t - 1) * S : 0);
    ans2 += 1ll * t * S;
    return max(ans1, ans2);
}

int main() {
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        scanf("%d%lld%lld%d", &n, &s, &m, &k);
        for (int i = 1; i <= n; ++i) {
            vis[i] = 0;
            scanf("%d", arr + i);
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) {
                vis[i] = 1;
                vec.clear();
                vec.push_back(arr[i]);
                for (ll it = (i + k - 1) % n + 1; !vis[it]; it = (it + k - 1) % n + 1) {
                    vis[it] = 1;
                    vec.push_back(arr[it]);
                }
                res = max(res, work(vec));
            }
        printf("%lld\n", max(0ll, s - res));
    }
    return 0;
}
