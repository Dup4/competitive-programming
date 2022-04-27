#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
inline void out(T s) {
    cout << s << "\n";
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
int n, sta[N], top;
string s;
char t[N];
bool ok(int n) {
    int cnt[2] = {0}, Max[2] = {0};
    for (int i = n; i >= 0; --i) {
        if (s[i] == '0')
            ++Max[0];
        else {
            ++cnt[0];
            Max[0] = max(Max[0], cnt[0]);
        }
        if (t[i] == '0')
            ++Max[1];
        else {
            ++cnt[1];
            Max[1] = max(Max[1], cnt[1]);
        }
        if (Max[0] != Max[1])
            return false;
    }
    return true;
}
void run() {
    n = s.size();
    top = 0;
    t[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1')
            sta[++top] = i;
        t[i] = '0';
        while (!ok(i)) {
            assert(top > 0);
            t[sta[top]] = '1';
            --top;
        }
    }
    t[n] = 0;
    cout << t << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> s) run();
    return 0;
}
