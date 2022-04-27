#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e6 + 10;
int n, k, w;
ll L[N], H[N], Al, Bl, Cl, Dl, Ah, Bh, Ch, Dh;

void run() {
    rd(n, k, w);
    for (int i = 1; i <= k; ++i) rd(L[i]);
    rd(Al, Bl, Cl, Dl);
    for (int i = 1; i <= k; ++i) rd(H[i]);
    rd(Ah, Bh, Ch, Dh);
    for (int i = k + 1; i <= n; ++i) {
        L[i] = ((Al * L[i - 2] + Bl * L[i - 1] + Cl) % Dl) + 1;
        H[i] = ((Ah * H[i - 2] + Bh * H[i - 1] + Ch) % Dh) + 1;
    }
    //	for (int i = 1; i <= n; ++i) dbg(i, L[i], H[i]);
    ll res = 1;
    ll width = 0, height = 0;
    ll pre = -1e9;
    int que[N], head = 1, tail = 0;
    for (int i = 1; i <= n; ++i) {
        while (head <= tail && L[que[head]] + w < L[i]) ++head;
        if (head > tail)
            height += H[i] * 2;
        else if (H[que[head]] < H[i]) {
            height -= H[que[head]] * 2;
            height += H[i] * 2;
        }
        while (head <= tail && H[que[tail]] <= H[i]) --tail;
        que[++tail] = i;
        chmax(pre, L[i]);
        width += (L[i] + w - pre) * 2;
        pre = L[i] + w;
        //	dbg(i, width, height);
        //	+ height);
        res = (res * ((width + height) % mod)) % mod;
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    //	while (_T--) run();
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
