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
int n, a[N];
void run() {
    for (int i = 1; i <= 2 * n; ++i) a[i] = i;
    do {
        vector<int> vec;
        for (int i = 1; i <= 2 * n; ++i) {
            int tot = 0;
            for (int j = 0; j < n; ++j) {
                tot += a[(i + j - 1) % (2 * n) + 1];
            }
            vec.push_back(tot);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        if (vec.size() == 1 || (vec.size() == 2 && vec[0] + 1 == vec[1])) {
            cout << "ok\n";
            return;
        }
    } while (next_permutation(a + 1, a + 1 + 2 * n));
    cout << "no\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
