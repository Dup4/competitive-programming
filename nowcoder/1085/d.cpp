#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define fi first
#define se second
#define endl "\n" 
using ll = long long;
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
int k1, k2; string s; 
int exgcd(int a, int b, int &x, int &y) {
    if (!a && !b) return -1;
    if (b == 0) { x = 1; y = 0; return a; }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
int inv(int a, int n) {
	int x, y;
	int d = exgcd(a, n, x, y);
	if (d == 1) return (x % n + n) % n;
	return -1;
}
inline int f(char c) {
	if (c >= 'A' && c <= 'Z') return c - 'A';
	return c - 'a';
}
void run() {
	cin >> s;
	for (auto &it : s) {
		bool F = 0;
		if (it >= 'A' && it <= 'Z') F = 1;
		int C = f(it);
		C = ((C - k2) % 26 + 26) % 26;
		C *= inv(k1, 26);
		C %= 26;
		if (F) C += 'A';
		else C += 'a';
		it = C;
	}
	cout << s << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> k1 >> k2) run();
	return 0;
}
