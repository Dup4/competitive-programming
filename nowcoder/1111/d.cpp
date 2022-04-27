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
using ull = unsigned long long;
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
inline void pt(T s) {
    cout << s << "\n";
}
template <class T>
inline void pt(vector<T> &vec) {
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
int n, m, h[N];
inline int ceil(int x, int y) {
    return (x + y - 1) / y;
}
void run() {
    priority_queue<int, vector<int>, greater<int> > pq[3];
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        int t = ceil(h[i], 3);
        res += t;
        pq[h[i] % 3].push(t);
    }
    int S = 0;
    for (int i = 0; i <= m; ++i) {
        if (i) {
            if (!pq[1].empty()) {
                int t = pq[1].top();
                pq[1].pop();
                --res;
                if (t > 1) {
                    pq[2].push(t - 1);
                }
            } else if (!pq[2].empty()) {
                int t = pq[2].top();
                pq[2].pop();
                --res;
                if (t > 1)
                    pq[0].push(t - 1);
            } else if (!pq[0].empty()) {
                int t = pq[0].top();
                pq[0].pop();
                pq[1].push(t);
            }
        }
        chadd(S, res);
    }
    pt(S);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
