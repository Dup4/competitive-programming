#include "iostream"
#define ll long long
using namespace std;
const int maxn = 1 << 17;
const int N = 1 << 17;
const ll mod = 998244353;
ll sqr2 = 116195171;
int n;
ll f[maxn], aa[N << 2], bb[N << 2], conv[N << 2];
int a[maxn];
ll wn[N << 2], rev[N << 2];

ll quick_pow(ll a, ll b, int mod) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = (res * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return res % mod;
}
ll inv(ll a, int mod) {
    return quick_pow(a, mod - 2, mod);
}

inline ll qpow(ll base, ll n, ll mod = 998244353) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}

struct NTT {
    static const int m1 = 469762049, m2 = 998244353, m3 = 1004535809, g = 3;
    static const ll M = 1ll * m1 * m2;
    int r[N], c[N], d[N], ans[3][N];
    void init(int fn, int fl) {
        for (int i = 0; i < fn; ++i) {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (fl - 1));
        }
    }
    void work(int n, ll *a, int opt, int mod) {
        for (int i = 0; i < n; ++i)
            if (i < r[i])
                swap(a[i], a[r[i]]);
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0, wn = qpow(g, (mod - 1) / (k << 1), mod); i < n; i += (k << 1))
                for (int j = 0, w = 1; j < k; ++j, w = 1ll * w * wn % mod) {
                    int x = a[i + j], y = 1ll * w * a[i + j + k] % mod;
                    a[i + j] = (x + y) % mod, a[i + j + k] = (x - y + mod) % mod;
                }
        if (opt == -1) {
            a[0] = 1ll * a[0] * qpow(n, mod - 2, mod) % mod;
            for (int i = 1, inv = qpow(n, mod - 2, mod); i <= n / 2; ++i) {
                a[i] = 1ll * a[i] * inv % mod;
                if (i != n - i)
                    a[n - i] = 1ll * a[n - i] * inv % mod;
                swap(a[i], a[n - i]);
            }
        }
    }
} ntt;

int NTT_init(int n_) {
    int step = 0;
    int n = 1;
    for (; n < n_; n <<= 1) step++;
    for (int i = 1; i < n; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    int g = quick_pow(3, (mod - 1) / n, mod);
    wn[0] = 1;
    for (int i = 1; i <= n; i++) wn[i] = wn[i - 1] * g % mod;
    return n;
}

void NTT(ll a[], int n, int f) {
    for (int i = 0; i < n; i++)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            int t = n / (k << 1);
            for (int j = 0; j < k; j++) {
                ll w = f == 1 ? wn[t * j] : wn[n - t * j];
                ll x = a[i + j];
                ll y = a[i + j + k] * w % mod;
                a[i + j] = (x + y) % mod;
                a[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
    if (f == -1) {
        ll Inv = inv(n, mod);
        for (int i = 0; i < n; i++) a[i] = a[i] * Inv % mod;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]]++;
    }
    for (int i = 0; i < 100001; i++) {
        aa[i] = f[i] * quick_pow(sqr2, (ll)i * i, mod) % mod;
        bb[i] = quick_pow(sqr2, (-(ll)i * i) % (mod - 1) + mod - 1, mod);
    }

    //	int m = 1e5;
    //	int fn = 1, fl = 0;
    //	while (fn <= m * 2) fn <<= 1, ++fl;
    //	ntt.init(fn, fl);
    //    ntt.work(fn, aa, 1, mod);
    //	ntt.work(fn, bb, 1, mod);
    //    for(int i = 0; i < m; i++)
    //        conv[i] = 1ll * aa[i] * bb[i] % mod;
    //    ntt.work(fn, conv, -1, mod);

    int m = NTT_init(1 << 18);
    NTT(aa, m, 1);
    NTT(bb, m, 1);
    for (int i = 0; i < m; i++) conv[i] = 1ll * aa[i] * bb[i] % mod;
    NTT(conv, m, -1);

    ll ans = 0;
    for (int i = 0; i < 100001; i++)
        ans = (ans + 1ll * f[i] * quick_pow(sqr2, 1ll * i * i, mod) % mod * conv[i] % mod) % mod;
    ans = (ans * 2) % mod;
    for (int i = 0; i < 100001; i++)
        ans = (ans - 1ll * f[i] * f[i] % mod * quick_pow(2, 1ll * i * i, mod) % mod + mod) % mod;
    cout << (ans + mod) % mod << endl;
    return 0;
}
