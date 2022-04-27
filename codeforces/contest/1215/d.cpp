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
constexpr int N = 2e5 + 10;
int n;
char s[N];
inline void A() {
    out("Monocarp");
}
inline void B() {
    out("Bicarp");
}
void run() {
    int cnt[2] = {0, 0}, sum[2] = {0, 0};
    cin >> (s + 1);
    int mid = n / 2;
    for (int i = 1; i <= mid; ++i) {
        if (isdigit(s[i]))
            sum[0] += s[i] - '0';
        else
            ++cnt[0];
    }
    for (int i = mid + 1; i <= n; ++i) {
        if (isdigit(s[i]))
            sum[1] += s[i] - '0';
        else
            ++cnt[1];
    }
    if (cnt[0] < cnt[1]) {
        cnt[1] -= cnt[0];
        cnt[0] = 0;
    } else {
        cnt[0] -= cnt[1];
        cnt[1] = 0;
    }
    if (cnt[0] == 0 && cnt[1] == 0) {
        if (sum[0] == sum[1])
            return B();
        return A();
    } else if (cnt[0]) {
        int t = sum[0] + 9 * cnt[0] / 2;
        if (t != sum[1])
            return A();
        return B();
    } else {
        int t = sum[1] + 9 * cnt[1] / 2;
        if (t != sum[0])
            return A();
        return B();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
