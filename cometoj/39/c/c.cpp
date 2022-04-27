#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
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
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
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
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
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
constexpr int N = 2e3 + 10, INF = 0x3f3f3f3f;
int n, m, K, a[N][N];
inline int query(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2)
        return 0;
    if (x1 <= 0 || y1 <= 0 || x2 <= 0 || y2 <= 0)
        return 0;
    return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}

vector<int> gao(int x) {
    vector<int> row, col;
    int unit = a[n][m] / (x + 1);
    int num = 0;
    for (int i = 1; i < n && (int)row.size() < x; ++i) {
        num += query(i, 1, i, m);
        if (num > unit)
            return vector<int>(K, INF);
        if (num == unit) {
            row.push_back(i);
            num = 0;
        }
    }
    if (row.size() != x)
        return vector<int>(K, INF);
    int y = K - x;
    if (unit % (y + 1))
        return vector<int>(K, INF);
    unit = unit / (y + 1);
    vector<int> cnt(x + 1, 0);
    for (int i = 1; i < m && (int)col.size() < y; ++i) {
        int pre = 0;
        int ok = 1;
        for (int j = 0; j < x; ++j) {
            cnt[j] += query(pre + 1, i, row[j], i);
            if (cnt[j] > unit) {
                return vector<int>(K, INF);
            }
            if (cnt[j] != unit)
                ok = 0;
            pre = row[j];
        }
        cnt[x] += query(pre + 1, i, n, i);
        if (cnt[x] > unit)
            return vector<int>(K, INF);
        if (cnt[x] != unit)
            ok = 0;
        if (ok) {
            cnt.clear();
            cnt.resize(x + 1);
            col.push_back(n - 1 + i);
        }
    }
    if ((int)(col.size() + row.size()) != K)
        return vector<int>(K, INF);
    for (auto &it : col) row.push_back(it);
    return row;
}

void run() {
    cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i) {
        static string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            a[i][j + 1] = (s[j] - '0') ^ 1;
            a[i][j + 1] += a[i - 1][j + 1] + a[i][j] - a[i - 1][j];
        }
    }
    vector<int> res(K, INF);
    for (int i = 0; i <= min(n - 1, K); ++i) {
        if (a[n][m] % (i + 1) == 0) {
            res = min(res, gao(i));
        }
    }
    if (res[0] == INF)
        pt("Impossible");
    else {
        for (int i = 0; i < K; ++i) cout << res[i] << " \n"[i == K - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = rd();
    while (_T--) run();
    return 0;
}
