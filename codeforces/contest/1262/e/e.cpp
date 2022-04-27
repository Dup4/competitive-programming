#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
int n, m;
vector<string> G, H;
vector<vector<int>> S;
int Move[][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {-1, -1},
        {-1, 1},
        {1, 1},
        {1, -1},
};

int getS(int x, int y, int x1, int y1) {
    if (x < 1 || y < 1 || x1 > n || y1 > m)
        return 1;
    return S[x1][y1] - S[x - 1][y1] - S[x1][y - 1] + S[x - 1][y - 1];
}

void get(int T) {
    H = vector<string>(n + 1, string(m + 1, '.'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (G[i - 1][j - 1] != 'X')
                continue;
            static int x[2], y[2];
            x[0] = i - T;
            y[0] = j - T;
            x[1] = i + T;
            y[1] = j + T;
            if (getS(x[0], y[0], x[1], y[1]) == 0) {
                H[i][j] = 'X';
            }
        }
    }
}

struct E {
    int x, y, s;
    E() {}
    E(int x, int y, int s) : x(x), y(y), s(s) {}
};

bool valid(int x, int y) {
    if (x < 1 || y < 1 || x > n || y > m || H[x][y] == 'X')
        return false;
    return true;
}

bool ok(int T) {
    get(T);
    queue<E> que;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (H[i][j] == 'X') {
                que.push(E(i, j, 0));
            }
        }
    }
    while (!que.empty()) {
        E e = que.front();
        que.pop();
        for (int i = 0; i < 8; ++i) {
            int nx = e.x + Move[i][0];
            int ny = e.y + Move[i][1];
            int ns = e.s + 1;
            if (ns <= T && valid(nx, ny)) {
                H[nx][ny] = 'X';
                que.push(E(nx, ny, ns));
            }
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (G[i][j] != H[i + 1][j + 1])
                return false;
    return true;
}

void run() {
    G = vector<string>(n);
    S = vector<vector<int>>(n + 5, vector<int>(m + 5, 0));
    for (auto &it : G) cin >> it;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            S[i + 1][j + 1] = S[i][j + 1] + S[i + 1][j] - S[i][j];
            if (G[i][j] == '.') {
                S[i + 1][j + 1] += 1;
            }
        }
    }
    int l = 1, r = n * m, res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (ok(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    pt(res);
    get(res);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << H[i][j];
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
