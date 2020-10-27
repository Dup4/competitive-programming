#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
const int N = 1e7 + 10;
#define all(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
int n, q;
int ans[N];

struct Add {
    ll t; int x;
    Add() {}
    Add(ll t, int x) : t(t), x(x) {}
    bool operator < (const Add &other) const {
        return t < other.t;
    }
};

struct Query {
    int f, id;
    ll t;
    Query() {}
    Query(int f, int id, ll t): f(f), id(id), t(t) {}
    bool operator < (const Query &other) const {
        return t < other.t;
    }
};

struct M {
    vector <Add> addVec;
    vector <Query> queryVec;
    void init() {
        addVec.clear();
        queryVec.clear();
    }
    M() {
        init();
    }
    void gao() {
        sort(all(addVec));
        sort(all(queryVec));
        int res = 0;
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
}m;

int main() {
    int _T; scanf("%d", &_T);
    while (_T--) {
        scanf("%d", &n);
        m.init();
        for (int i = 1; i <= n; ++i) {
            ll t;
            scanf("%llu", &t);
            m.addVec.emplace_back(t, 1);
        }
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i) ans[i] = 0;
        for (int i = 1; i <= q; ++i) {
            ll l, r;
            scanf("%llu%llu", &l, &r);
            m.queryVec.emplace_back(1, i, r);
            if (l > 0) m.queryVec.emplace_back(-1, i, l - 1);
        }
        m.gao();
        for (int i = 1; i <= q; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}