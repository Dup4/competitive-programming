#include <bits/stdc++.h>
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
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
typedef double db;
typedef pair<int, db> pID;
#define fi first
#define se second
const int N = 2e5 + 10;
int n;

pID op(pID a, pID b) {
    if (a.fi > b.fi)
        return a;
    if (a.fi < b.fi)
        return b;
    return pID(a.fi, a.se + b.se);
}

struct Hash {
    vector<int> a;
    int &operator[](int x) {
        return a[x - 1];
    }
    int size() {
        return a.size();
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hy, hz;

struct BIT {
    pID a[N];
    int n, pos[N], POS;
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof(a[0]) * (n + 5));
        memset(pos, 0, sizeof(pos[0]) * (n + 5));
        POS = 0;
    }
    void update(int x, pID v) {
        for (; x <= n; x += x & -x) {
            if (pos[x] == POS) {
                a[x] = op(a[x], v);
            } else {
                a[x] = v;
                pos[x] = POS;
            }
        }
    }
    pID query(int x) {
        pID res = pID(0, 1);
        for (; x; x -= x & -x) {
            if (pos[x] == POS) {
                res = op(res, a[x]);
            }
        }
        return res;
    }
} bit;

struct E {
    int x, y, z;
} e[N];

struct CDQ {
    struct node {
        int x, y, z;
        bool operator<(const node &other) const {
            return x < other.x;
        }
    } t[N];
    static bool cmp(const node &a, const node &b) {
        if (a.y == b.y)
            return a.x < b.x;
        return a.y < b.y;
    }
    int tot;
    void init() {
        tot = 0;
    }
    void addNode(int x, int y, int z) {
        t[++tot] = {x, y, z};
    }
    pID f[N];
    void solve(int l, int r) {
        if (l == r) {
            if (f[l].fi < 1)
                f[l] = pID(1, 1);
            return;
        }
        int mid = (l + r) >> 1;
        solve(l, mid);
        sort(t + l, t + r + 1, cmp);
        ++bit.POS;
        for (int i = l; i <= r; ++i) {
            if (t[i].x <= mid) {
                bit.update(t[i].z, f[t[i].x]);
            } else {
                pID tmp = bit.query(t[i].z);
                ++tmp.fi;
                f[t[i].x] = tmp;
                //	f[t[i].x] = op(f[t[i].x], tmp);
            }
        }
        solve(mid + 1, r);
    }
    void gao() {
        bit.init(hz.size());
        memset(f, 0, sizeof(f[0]) * (tot + 5));
        sort(t + 1, t + 1 + tot);
        solve(1, tot);
    }
} cdqF, cdqG;

int main() {
    while (scanf("%d", &n) != EOF) {
        hy.init();
        hz.init();
        for (int i = 1; i <= n; ++i) {
            e[i].x = i;
            scanf("%d%d", &e[i].y, &e[i].z);
            hy.add(e[i].y);
            hz.add(e[i].z);
        }
        hy.gao();
        hz.gao();
        for (int i = 1; i <= n; ++i) {
            e[i].y = hy.get(e[i].y);
            e[i].z = hz.get(e[i].z);
        }
        cdqF.init();
        for (int i = 1; i <= n; ++i) {
            cdqF.addNode(e[i].x, hy.size() - e[i].y + 1, hz.size() - e[i].z + 1);
        }
        cdqF.gao();
        cdqG.init();
        for (int i = 1; i <= n; ++i) {
            cdqG.addNode(n - e[i].x + 1, e[i].y, e[i].z);
        }
        cdqG.gao();
        pID res = pID(0, 0);
        for (int i = 1; i <= n; ++i) res = op(res, cdqF.f[i]);
        printf("%d\n", res.fi);
        for (int i = 1; i <= n; ++i) {
            int j = n - i + 1;
            pID _f = cdqF.f[i], _g = cdqG.f[j];
            //	dbg(i, _f.fi, _f.se, _g.fi, _g.se);
            db ans = 0;
            if (_f.fi + _g.fi - 1 == res.fi) {
                ans = _f.se * _g.se / res.se;
            }
            printf("%.5f%c", ans, " \n"[i == n]);
        }
    }
    return 0;
}
