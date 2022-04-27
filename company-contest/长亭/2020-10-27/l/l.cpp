#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
int n, m;
ll ans[N];

struct Add {
    ll t, x;
    Add() {}
    Add(ll t, ll x) : t(t), x(x) {}
    bool operator<(const Add &other) const {
        return t < other.t;
    }
};

struct Query {
    int f, id;
    ll t;
    Query() {}
    Query(int f, int id, ll t) : f(f), id(id), t(t) {}
    bool operator<(const Query &other) const {
        return t < other.t;
    }
};

struct M {
    vector<Add> addVec;
    vector<Query> queryVec;
    M() {
        addVec.clear();
        queryVec.clear();
    }
    void gao() {
        sort(all(addVec));
        sort(all(queryVec));
        ll res = 0;
        int pos = -1;
        int len = SZ(addVec);
        for (auto &i : queryVec) {
            while (pos + 1 < len && addVec[pos + 1].t <= i.t) {
                ++pos;
                res += addVec[pos].x;
            }
            ans[i.id] += res * i.f;
        }
    }
};

map<string, M> mp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    mp.clear();
    for (int i = 1; i <= n; ++i) {
        ll t, x;
        string s;
        cin >> t >> s >> x;
        mp[s].addVec.emplace_back(t, x);
    }
    for (int i = 1; i <= m; ++i) {
        ll l, r;
        string s;
        cin >> l >> r >> s;
        mp[s].queryVec.emplace_back(1, i, r);
        mp[s].queryVec.emplace_back(-1, i, l - 1);
    }
    for (auto &it : mp) it.second.gao();
    for (int i = 1; i <= m; ++i) cout << ans[i] << "\n";
    return 0;
}