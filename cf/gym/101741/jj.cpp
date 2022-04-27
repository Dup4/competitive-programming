#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const ll maxn = 2e5 + 5;
ll lv[maxn][21], rv[maxn][21];  //当然也可以只用一个数组
ll ans[maxn];
ll q[maxn][2];
ll a[maxn];
ll n, m, qn;
vector<ll> id;

void divide(ll l, ll r, vector<ll> id) {
    ll mid = (l + r) / 2;

    for (ll i = mid + 1; i >= l; --i)
        for (ll j = 0; j < m; ++j) lv[i][j] = 0;
    lv[mid + 1][0] = 1;

    for (ll i = mid; i <= r; ++i)
        for (ll j = 0; j < m; ++j) rv[i][j] = 0;
    rv[mid][0] = 1;

    for (ll i = mid; i >= l; --i)  // lv范围是[l, mid]
        for (ll j = m - 1; j >= 0; --j)
            lv[i][j] = (lv[i][j] + lv[i + 1][j]) % mod + lv[i + 1][(j - a[i] + m) % m] % mod;

    for (ll i = mid + 1; i <= r; ++i)  // rv范围是[mid+1, r]
        for (ll j = m - 1; j >= 0; --j)
            rv[i][j] = (rv[i][j] + rv[i - 1][j]) % mod + rv[i - 1][(j - a[i] + m) % m] % mod;

    vector<ll> id_l, id_r;
    for (ll i = 0; i < id.size(); ++i) {
        ll l = q[id[i]][0], r = q[id[i]][1], _id = id[i];  //注意这里的l，r是询问区间的，不是函数形参
        if (l <= mid && r > mid) {
            ans[_id] = (lv[l][0] * rv[r][0]) % mod;
            for (ll j = 1; j < m; ++j) {
                ans[_id] += lv[l][j] * rv[r][m - j];
                ans[_id] %= mod;
            }
        } else if (r <= mid)
            id_l.push_back(_id);
        else
            id_r.push_back(_id);
    }
    if (id_l.size() && l < mid)
        divide(l, mid, id_l);
    if (id_r.size() && r > mid + 1)
        divide(mid + 1, r, id_r);
    //如果区间[l,r]只有两个点就没必要分治下去了
}

int main() {
    std::ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        for (ll i = 1; i <= n; ++i) {
            cin >> a[i];
            a[i] %= m;
        }

        cin >> qn;
        for (ll i = 1; i <= qn; ++i) {
            cin >> q[i][0] >> q[i][1];
            if (q[i][0] == q[i][1]) {
                if (a[q[i][0]] > 0)
                    ans[i] = 1;
                else
                    ans[i] = 2;
            } else {
                id.push_back(i);
            }
        }
        divide(1, n, id);

        for (ll i = 1; i <= qn; ++i) cout << ans[i] << endl;
    }

    return 0;
}
