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
constexpr int mod = 1e9 + 7;
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
constexpr int N = 5e2 + 10;
int n, a[N], f[N], sta[N], top;

bool increse(int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        if (a[i - 1] >= a[i])
            return 0;
    }
    return 1;
}

bool decrese(int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        if (a[i - 1] <= a[i])
            return 0;
    }
    return 1;
}

bool ok1(int l, int r) {
    if (l == r)
        return 1;
    if (a[l] == a[l + 1] && increse(l + 1, r))
        return 1;
    if (a[r] == a[r - 1] && decrese(l, r - 1))
        return 1;
    return 0;
}

bool ok(int l, int r) {
    top = 0;
    sta[++top] = a[l];
    for (int i = l + 1; i <= r; ++i) {
        sta[++top] = a[i];
        while (top >= 2 && sta[top] == sta[top - 1]) {
            int tmp = sta[top];
            top -= 2;
            sta[++top] = tmp + 1;
        }
    }
    return top == 1;
}

void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(f, 0, sizeof f);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        for (int j = 0; j < i; ++j) {
            if (ok(j + 1, i)) {
                chmin(f[i], f[j] + 1);
            }
        }
    }
    pt(f[n]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
