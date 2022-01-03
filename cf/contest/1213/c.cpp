#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
using LL = long long;
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
using VI = vector <int>;
using VL = vector <ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }
template <class T> inline void out(T s) { cout << s << "\n"; }
template <class T> inline void out(vector <T> &vec) { for (auto &it : vec) cout << it << " "; cout << endl; } 
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
constexpr int N = 1e5 + 10;
ll n, m;
LL gao(LL a, LL b, LL c, LL n) {
    if (a == 0) {
        return (n + 1) * (b / c);
    }
    if (a >= c || b >= c) {
        LL tmp = gao(a % c, b % c, c, n);
        LL res = tmp + (a / c) * n * (n + 1) / 2 + (b / c) * (n + 1);
        return res;
    }
    LL m = (a * n + b) / c;
    LL tmp = gao(c, c - b - 1, a, m - 1);
    LL res = (n * m - tmp);
    return res;
}
LL sum_2(LL n) {
	return n * (n + 1) / 2;
}
void out(LL n) {
	if (n / 10) out(n / 10);
	putchar(n % 10 + '0');
}

void run() {
	cin >> n >> m;
	LL res = (LL)m * sum_2(n / m);
	res -= (LL)10 * gao(m, 0, 10, n / m);
	out(res);
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
