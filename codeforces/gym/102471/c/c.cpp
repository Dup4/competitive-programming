#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 998244353;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
}
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
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 1e5 + 10;
int n, K;

ll inv(int x) {
    return qpow(x, mod - 2);
}

int pri[N], check[N], priK[N], priSK[N];
vector<int> gao(vector<int> &f, vector<int> &g) {
    vector<int> res(n + 1, 0);
    memset(check, 0, sizeof check);
    *pri = 0;
    res[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            priK[i] = 1;
            priSK[i] = i;
            res[i] = (1ll * f[1] * g[i] % mod + 1ll * f[i] * g[1] % mod) % mod;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] > n)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                priK[i * pri[j]] = priK[i] + 1;
                priSK[i * pri[j]] = priSK[i] * pri[j];
                if (i / priSK[i] == 1) {
                    int cnt = priK[i * pri[j]];
                    vector<int> vec(cnt + 1);
                    vec[0] = 1;
                    for (int k = 1; k <= cnt; ++k) vec[k] = vec[k - 1] * pri[j];
                    for (int k = 0; k <= cnt; ++k) {
                        res[i * pri[j]] = (res[i * pri[j]] + 1ll * f[vec[k]] * g[vec[cnt - k]] % mod) % mod;
                    }
                } else {
                    res[i * pri[j]] = 1ll * res[i / priSK[i]] * res[priSK[i] * pri[j]] % mod;
                }
            } else {
                priK[i * pri[j]] = 1;
                priSK[i * pri[j]] = pri[j];
                res[i * pri[j]] = 1ll * res[i] * res[pri[j]] % mod;
            }
        }
    }
    return res;
}

vector<int> gao1(vector<int> &f, vector<int> &g) {
    static vector<int> res;
    res = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            chadd(res[j], 1ll * f[i] * g[j / i] % mod);
        }
    }
    return res;
}

void run() {
    //	int phi = mod - 1;
    vector<int> base(n + 1), res(n + 1);
    for (int i = 1; i <= n; ++i) rd(base[i]);
    int need = inv(K);
    res[1] = 1;
    while (need) {
        if (need & 1)
            res = gao(res, base);
        base = gao(base, base);
        need >>= 1;
    }
    for (int i = 1; i <= n; ++i) cout << res[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> K) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
