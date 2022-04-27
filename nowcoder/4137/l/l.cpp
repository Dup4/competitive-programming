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
constexpr int N = 1e2 + 10, INF = 0x3f3f3f3f;
int n, m, sx, sy, a[N][N];
char g[N][N];

struct E {
    int x, y, w;
};

int Mfoot[][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int Move[][2][2] = {
        {2, -1, 2, 1},
        {-2, -1, -2, 1},
        {1, 2, -1, 2},
        {1, -2, -1, -2},
};

bool ok(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > m || g[x][y] == 'X')
        return false;
    return true;
}

void bfs() {
    memset(a, 0x3f, sizeof a);
    a[sx][sy] = 0;
    queue<E> que;
    que.push({sx, sy, 0});
    while (!que.empty()) {
        E it = que.front();
        que.pop();
        int x = it.x, y = it.y, w = it.w;
        for (int i = 0; i < 4; ++i) {
            if (ok(x + Mfoot[i][0], y + Mfoot[i][1])) {
                for (int j = 0; j < 2; ++j) {
                    int nx = x + Move[i][j][0];
                    int ny = y + Move[i][j][1];
                    if (ok(nx, ny) && a[nx][ny] > w + 1) {
                        a[nx][ny] = w + 1;
                        que.push({nx, ny, w + 1});
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == INF)
                a[i][j] = -1;
}

void run() {
    for (int i = 1; i <= n; ++i) {
        cin >> (g[i] + 1);
        for (int j = 1; j <= m; ++j) {
            if (g[i][j] == 'M') {
                sx = i;
                sy = j;
            }
        }
    }
    bfs();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cout << a[i][j] << " \n"[j == m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
