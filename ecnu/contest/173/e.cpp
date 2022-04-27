#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define M 1000010
#define INF 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
const ll p = (ll)1e9 + 7;
vector<vector<pii> > fac;
int prime[M];
bool check[M];
void init() {
    fac.clear();
    fac.resize(M);
    memset(check, 0, sizeof check);
    prime[0] = 0;
    for (int i = 2; i < M; ++i) {
        if (!check[i]) {
            for (int j = i; j < M; j += i) {
                fac[j].push_back(pii(i, 1));
                check[j] = 1;
            }
        }
    }
    fac[1].push_back(pii(1, 1e7));
    for (int i = 2; i < M; ++i) {
        for (auto &it : fac[i]) {
            int t = i;
            int res = 0;
            while (t % it.fi == 0) {
                t /= it.fi;
                ++res;
            }
            it.se = res;
        }
        reverse(fac[i].begin(), fac[i].end());
    }
}

ll qmod(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        n >>= 1;
    }
    return res;
}

int n, m, a[N];
struct SEG {
    struct node {
        vector<pii> vec;
        int sum, Min, lazy;
        node() {
            sum = Min = lazy = 0;
            vec.clear();
        }
        void add(int x) {
            sum += x;
            Min += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Min = min(Min, other.Min);
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].vec = fac[a[l]];
            t[id].sum = t[id].Min = t[id].vec.back().se;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void pushdown(int id) {
        int &x = t[id].lazy;
        if (x == 0) {
            return;
        }
        t[id << 1].add(x);
        t[id << 1 | 1].add(x);
        x = 0;
    }
    void update(int id, int l, int r, int ql, int qr, int x) {
        if (l >= ql && r <= qr && t[id].Min + x > 0) {
            t[id].add(x);
            return;
        }
        if (l == r) {
            t[id].add(x);
            if (t[id].sum == 0) {
                t[id].vec.pop_back();
                if (t[id].vec.empty()) {
                    t[id].vec.push_back(pii(1, 1e7));
                }
                t[id].sum = t[id].Min = t[id].vec.back().se;
            }
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, x);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    ll query(int id, int l, int r, int pos) {
        if (l == r) {
            ll res = 1;
            t[id].vec.back().se = t[id].sum;
            for (auto it : t[id].vec) {
                res = res * qmod(it.fi, it.se) % p;
            }
            return res;
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

int main() {
    init();
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        seg.build(1, 1, n);
        int op, l, r, x;
        while (m--) {
            scanf("%d", &op);
            switch (op) {
                case 1:
                    scanf("%d%d", &l, &r);
                    seg.update(1, 1, n, l, r, 1);
                    break;
                case 2:
                    scanf("%d%d", &l, &r);
                    seg.update(1, 1, n, l, r, -1);
                    break;
                case 3:
                    scanf("%d\n", &x);
                    printf("%lld\n", seg.query(1, 1, n, x));
                    break;
                default:
                    assert(0);
            }
        }
    }
    return 0;
}
