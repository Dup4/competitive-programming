#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e4 + 10;
ll n, m, s, k, len, p;
ll ans, tmp, cnt, ct, tp, f;
vector<ll> vc[maxn];
ll a[maxn], q[maxn], stk[maxn], sum[maxn];
bool vis[maxn];
ll cal(vector<ll>& v, ll tmp) {
    ll res = 0;
    ll nn = v.size();
    ll he = 0, ta = 0;
    for (ll i = 0; i < nn; i++) q[i + nn] = q[i] = v[i];
    nn *= 2;
    for (ll i = 0; i < nn; i++) {
        if (i == 0)
            sum[i] = q[i];
        else
            sum[i] = sum[i - 1] + q[i];
        if (i < tmp)
            res = max(res, sum[i]);  //注意我注释的这几个地方，都曾经写错过
        while (he < ta && stk[he] + tmp < i) he++;
        if (he < ta)
            res = max(res, sum[i] - sum[stk[he]]);  //
        while (he < ta && sum[stk[ta - 1]] >= sum[i]) ta--;
        stk[ta++] = i;  //
    }
    return res;
}
ll go(vector<ll>& v, ll m) {
    ll sz = v.size();
    ll sm = accumulate(v.begin(), v.end(), 0);
    // cout<<"%";
    ll len1 = m / sz, len2 = m % sz;
    // cout<<"*";
    ll m1 = cal(v, len2);
    ll m2 = cal(v, sz);
    m1 += max((ll)0, sm) * len1;
    m2 += max((ll)0, sm) * ((len1 >= 1) ? (len1 - 1) : 0);
    return max(m1, m2);
}
int main() {
    int T, cas = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld%lld", &n, &s, &m, &k);
        for (int i = 0; i < n; i++) {
            vis[i] = false;
            vc[i].clear();
            scanf("%lld", &a[i]);
        }
        cnt = -1;
        ans = 0;
        for (ll i = 0; i < n; i++)
            if (!vis[i]) {
                cnt++;
                vis[i] = 1;
                vc[cnt].push_back(a[i]);
                for (ll j = (i + k) % n; (j != i) && (!vis[j]); j = (j + k) % n) {
                    vis[j] = 1;
                    vc[cnt].push_back(a[j]);
                }
                ans = max(ans, go(vc[i], m));
                // cout<<ans<<endl;
            }
        printf("Case #%d: %lld\n", cas++, max(0ll, s - ans));
    }
    return 0;
}
