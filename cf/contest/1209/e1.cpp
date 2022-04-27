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
constexpr int N = 1e2 + 10;
int n, m, a[N][5], b[N][5], c[N][5][5], Max[5];
int gao1() {
    vector<int> vec;
    for (int i = 1; i <= m; ++i) vec.push_back(b[i][1]);
    sort(vec.begin(), vec.end(), [&](int x, int y) {
        return x > y;
    });
    int sum = 0;
    for (int i = 0, sze = vec.size(); i < min(n, sze); ++i) sum += vec[i];
    return sum;
}
int gao2() {
    if (n == 1)
        return b[m][1];
    if (n == 2)
        return b[m][1] + b[m][2];
    int res = 0;
    if (n >= 3) {
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int sum = 0;
                for (int k = 1; k <= n; ++k) {
                    sum += max(a[m][k], c[i][j][k]);
                }
                res = max(res, sum);
            }
        }
    }
    if (n == 4) {
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= n; ++k) Max[k] = max(a[m][k], c[i][j][k]);
                for (int k = i + 1; k < m; ++k) {
                    for (int o = 1; o <= n; ++o) {
                        int sum = 0;
                        for (int l = 1; l <= n; ++l) {
                            sum += max(Max[l], c[k][o][l]);
                        }
                        res = max(res, sum);
                    }
                }
            }
        }
    }
    return res;
}
void run() {
    cin >> n >> m;
    int res = 0;
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= m; ++i) cin >> a[i][j], b[i][j] = a[i][j];
    }
    for (int i = 1; i <= m; ++i) res = max(res, accumulate(a[i] + 1, a[i] + 1 + n, 0));
    for (int i = 1; i <= m; ++i)
        sort(b[i] + 1, b[i] + 1 + n, [&](int x, int y) {
            return x > y;
        });
    res = max(res, gao1());
    int pos = 1;
    for (int i = 2; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (b[i][j] != b[pos][j]) {
                if (b[i][j] > b[pos][j])
                    pos = i;
                break;
            }
        }
    }
    if (m != pos)
        for (int i = 1; i <= n; ++i) swap(a[m][i], a[pos][i]), swap(b[m][i], b[pos][i]);
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j <= n; ++j) {
            c[i][1][j] = a[i][j];
        }
        for (int j = 2; j <= n; ++j) {
            for (int k = n; k >= 2; --k) c[i][j][k] = c[i][j - 1][k - 1];
            c[i][j][1] = c[i][j - 1][n];
        }
    }
    res = max(res, gao2());
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T;
    cin >> _T;
    while (_T--) run();
    return 0;
}
