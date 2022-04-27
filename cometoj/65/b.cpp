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
constexpr int N = 1e5 + 10;
int n, a[N], b[N];
struct node {
    int tp, x;
};
vector<vector<node>> add;
bool check(int x) {
    //	cout << "########   " << x << endl;
    queue<int> q[4];
    add.clear();
    add.resize(n + 1);
    for (int i = 1; i < N; ++i)
        if (a[i]) {
            q[a[i]].push(i);
        }
    for (int i = 1; i <= n; ++i) {
        bool F = 0;
        for (auto &it : add[i]) {
            q[it.tp].push(it.x);
        }
        for (int j = 3; j >= 1; --j) {
            if (!q[j].empty()) {
                int u = q[j].front();
                q[j].pop();
                //	cout << i << " " << u << endl;
                if (j > 1) {
                    if (i + x + 1 <= n)
                        add[i + x + 1].push_back({j - 1, u});
                    else
                        return 0;
                }
                F = 1;
                break;
            }
        }
        if (!F)
            return 0;
    }
    return 1;
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + 1 + n);
    b[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] == a[i - 1])
            b[i] = b[i - 1];
        else
            b[i] = b[i - 1] + 1;
    }
    memset(a, 0, sizeof a);
    for (int i = 1; i <= n; ++i) ++a[b[i]];
    int l = 0, r = n, res = 0;
    while (r - l >= 0) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
