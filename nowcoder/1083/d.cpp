#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define fi first
#define se second
#define endl "\n"
using ll = long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
using VI = vector<int>;
using VL = vector<ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
    else if (x < 0)
        x += mod;
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
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
template <class T>
inline void out(vector<T> &vec) {
    for (auto &it : vec) cout << it << " ";
    cout << endl;
}
inline ll gcd(ll a, ll b) {
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
constexpr int N = 4e2 + 10;
constexpr int INF = 0x3f3f3f3f;
int n, q;
vector<vector<int>> G;
int l, r, a[N], b[N], Mx[N], My[N], dx[N], dy[N], dis;
bool used[N];
bool SearchP() {
    queue<int> que;
    dis = INF;
    memset(dx, -1, sizeof dx);
    memset(dy, -1, sizeof dy);
    for (int i = l; i <= r; ++i) {
        if (Mx[i] == -1) {
            que.push(i);
            dx[i] = 0;
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (dx[u] > dis)
            break;
        for (auto &v : G[u]) {
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (My[v] == -1)
                    dis = dy[v];
                else {
                    dx[My[v]] = dy[v] + 1;
                    que.push(My[v]);
                }
            }
        }
    }
    return dis != INF;
}
bool DFS(int u) {
    for (auto &v : G[u]) {
        if (!used[v] && dy[v] == dx[u] + 1) {
            used[v] = true;
            if (My[v] != -1 && dy[v] == dis)
                continue;
            if (My[v] == -1 || DFS(My[v])) {
                My[v] = u;
                Mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch() {
    int res = 0;
    memset(Mx, -1, sizeof Mx);
    memset(My, -1, sizeof My);
    while (SearchP()) {
        memset(used, 0, sizeof used);
        for (int i = l; i <= r; ++i) {
            if (Mx[i] == -1 && DFS(i))
                ++res;
        }
    }
    return res;
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    G.clear();
    G.resize(N);
    for (int i = 1; i <= n; ++i)
        for (int j = a[i]; j <= b[i]; ++j) G[j].push_back(i);
    for (int i = 1; i <= q; ++i) {
        cin >> l >> r;
        cout << MaxMatch() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> q) run();
    return 0;
}
