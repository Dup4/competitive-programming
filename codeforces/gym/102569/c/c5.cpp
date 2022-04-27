#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) (int(x.size()))
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}
using ll = long long;
using pII = pair<int, int>;
const int N = 4e5 + 10;
int n;
pII p[N];
ll K;

int a[N];

struct Hash {
    int a[N];
    int size() {
        return *a;
    }
    void init() {
        *a = 0;
    }
    void add(int x) {
        a[++*a] = x;
    }
    void gao() {
        sort(a + 1, a + 1 + *a);
        *a = unique(a + 1, a + 1 + *a) - a - 1;
    }
    int get(int x) {
        return lower_bound(a + 1, a + 1 + *a, x) - a;
    }
} hy;

struct BIT {
    int a[N], n;
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof(a[0]) * (n + 5));
    }
    void update(int x, int v) {
        for (; x <= n; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

struct E {
    int op, x, l, r;
    inline bool operator<(const E& other) const {
        return x < other.x;
    }
};

inline int get(int x) {
    return lower_bound(a + 1, a + 1 + *a, x) - a;
}

E A[N], B[N], vec[N];

inline ll calc(int dis) {
    ll res = 0;
    *a = 0;
    for (int i = 1; i <= n; ++i) {
        a[++*a] = p[i].se;
        a[++*a] = p[i].se - dis;
        a[++*a] = p[i].se + dis;
    }
    sort(a + 1, a + 1 + *a);
    *a = unique(a + 1, a + 1 + *a) - a - 1;
    int m = *a;
    int cA = 0, cB = 0, cVec = 0;
    for (int i = n; i >= 1; --i) {
        int l = get(p[i].se - dis), r = get(p[i].se + dis);
        A[++cA] = {-1, p[i].fi - dis - 1, l, r};
        B[++cB] = {1, p[i].fi + dis, l, r};
    }
    for (int i = 1, sze = n * 2; i <= sze; ++i) {
        if (!cA)
            vec[++cVec] = B[cB--];
        else if (!cB)
            vec[++cVec] = A[cA--];
        else if (A[cA].x < B[cB].x) {
            vec[++cVec] = A[cA--];
        } else {
            vec[++cVec] = B[cB--];
        }
    }
    int pos = 0;
    bit.init(m);
    for (int i = 1; i <= cVec; ++i) {
        while (pos < n && p[pos + 1].fi <= vec[i].x) {
            ++pos;
            bit.update(get(p[pos].se), 1);
        }
        res += bit.query(vec[i].l, vec[i].r) * vec[i].op;
    }
    res -= n;
    res /= 2;
    return res;
}

int main() {
    scanf("%d%lld", &n, &K);
    for (int i = 1, _x, _y; i <= n; ++i) {
        scanf("%d%d", &_x, &_y);
        p[i].fi = _x + _y;
        p[i].se = _x - _y;
    }
    sort(p + 1, p + 1 + n);
    //	for (int i = 1; i <= n; ++i)
    //		dbg(i, p[i].fi, p[i].se);
    int l = 0, r = 4e8, res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (calc(mid) >= K) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", res);
    return 0;
}
