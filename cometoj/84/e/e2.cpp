#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
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
#define fi first
#define se second
const int mod = 998244353;
const int N = 1e6 + 10;
int n, a[N];
struct E {
    int p, l, r, g;
};
vector<vector<E>> vec;
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
inline void chadd(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}

void init() {
    vector<E> pre, now;
    for (int i = 1; i <= n; ++i) {
        now.clear();
        pre.push_back({i, i, i, a[i]});
        for (auto &it : pre) {
            if (now.empty()) {
                now.push_back({i, it.l, it.r, gcd(it.g, a[i])});
            } else {
                int g = gcd(it.g, a[i]);
                if (g == now.back().g) {
                    now.back().r = it.r;
                } else {
                    now.push_back({i, it.l, it.r, g});
                }
            }
        }
        for (auto &it : now) {
            vec[it.g].push_back(it);
        }
        pre = now;
    }
}

vector<pII> get(int x) {
    vector<int> tmp[3], res;
    for (auto &it : vec[x]) {
        tmp[0].push_back(it.p);
        tmp[1].push_back(it.l - 1);
        tmp[1].push_back(it.l);
        tmp[2].push_back(it.r - 1);
        tmp[2].push_back(it.r);
    }
    for (int i = 0; i < 3; ++i) {
        vector<int> tt(tmp[i].size() + res.size());
        merge(tmp[i].begin(), tmp[i].end(), res.begin(), res.end(), tt.begin());
        res = tt;
    }
    res.erase(unique(res.begin(), res.end()), res.end());
    vector<pII> h;
    for (auto &it : res) {
        if (!h.empty())
            h.back().se = it - h.back().fi;
        h.push_back(pII(it, 1));
    }
    return h;
}

struct W {
    int p, x, y;
};

pII gao(int x) {
    if (vec[x].empty())
        return pII(0, 0);
    vector<pII> h = get(x);
    int l = 0, r = -1;
    int ql = 0, qr = 0;
    vector<W> g;
    g.push_back({0, 0, 1});
    pII pre = pII(0, 0), res = pII(0, 0);
    for (auto &it : vec[x]) {
        for (; r < 0 || h[r].fi < it.r - 1;) {
            ++r;
            while (qr < (int)g.size() - 1 && g[qr + 1].p <= h[r].fi) ++qr;
            if (g[qr].x > pre.fi) {
                pre = pII(g[qr].x, 1ll * g[qr].y * h[r].se % mod);
            } else if (g[qr].x == pre.fi) {
                chadd(pre.se, 1ll * g[qr].y * h[r].se % mod);
            }
        }
        for (; h[l].fi < it.l - 1;) {
            while (ql < (int)g.size() - 1 && g[ql + 1].p <= h[l].fi) ++ql;
            if (g[ql].x == pre.fi) {
                chadd(pre.se, (1ll * -g[ql].y * h[l].se % mod + mod) % mod);
            }
            ++l;
        }
        pII now = pre;
        ++now.fi;
        if (now.fi > res.fi)
            res = now;
        else if (now.fi == res.fi)
            chadd(res.se, now.se);
        g.push_back({it.p, res.fi, res.se});
    }
    return res;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        vec.clear();
        vec.resize(N);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        init();
        pII res = pII(0, 0);
        for (int i = 1; i <= 1000000; ++i) {
            pII tmp = gao(i);
            if (tmp.fi > res.fi) {
                res = tmp;
            } else if (tmp.fi == res.fi) {
                chadd(res.se, tmp.se);
            }
        }
        printf("%d %d\n", res.fi, res.se);
    }
    return 0;
}
