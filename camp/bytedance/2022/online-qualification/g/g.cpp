#include <bits/stdc++.h>
#include <thread>
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

inline ll qpow(ll base, ll n, ll mod) {
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
constexpr int MAXN = 1e5;
constexpr int MAXK = 4e4;
int n;

int tot_thread = 16, tot_machine = 4, now_machine = 0;

// int moda = 39989, modb = 423;
// int ax[N], bx[N];

int pri[N], check[N];
void sieve() {
    memset(check, 0, sizeof check);
    *pri = 0;
    for (int i = 2; i <= MAXK; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] > MAXK)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

bool test(int moda, int modb) {
    // vector<int> ax(0, N), bx(0, N);
    int ax, bx;
    set<pair<int, int>> se;
    for (int i = 1; i <= MAXN; ++i) {
        ax = qpow(i, i, moda);
        bx = qpow(i, i, modb);
        se.insert(make_pair(ax, bx));
    }

    return se.size() == MAXN;
}

void get(int n, int tot, int moda) {
    for (int i = MAXK; i >= 1; --i) {
        if (i % tot != n)
            continue;

        if (test(moda, i)) {
            printf("ok %d %d\n", moda, i);
            exit(0);
        }

        printf("end %d %d\n", moda, i);
    }
}

void p_get(int moda) {
    vector<thread> th;
    for (int i = 0; i < tot_thread; ++i) {
        th.emplace_back([&, i = i]() {
            get(i, tot_thread, moda);
        });
    }

    for (auto &t : th) {
        t.join();
    }
}

void pp_get() {
    for (int i = *pri; i >= 1; --i) {
        if (i % tot_machine == now_machine) {
            p_get(pri[i]);
        }
    }
}

void run() {}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);
    // cout << fixed << setprecision(20);

    // sieve();

    // for (int i = 1; i <= *pri; ++i)
    // {
    // 	cout << pri[i] << " \n"[i == *pri];
    // }

    // cout << *pri << endl;
    // pp_get();

    // cout << test(39679, 39839) << endl;

    // cout << test(moda, modb);
    // init();
    // int _T = nextInt();
    // while (_T--)
    // run();
    //  for (int kase = 1; kase <= _T; ++kase) {
    //      cout << "Case #" << kase << ": ";
    //      run();
    //  }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
