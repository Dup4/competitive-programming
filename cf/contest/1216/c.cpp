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
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
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
int n;
struct node {
	int x[2], y[2];
	void scan() { cin >> x[0] >> y[0] >> x[1] >> y[1]; x[0] *= 2; y[0] *= 2; x[1] *= 2; y[1] *= 2; }
}a[3];
inline int cross (int x1, int x2, int y1, int y2) {
	x1 = max(x1, y1);
	x2 = min(x2, y2);
	return max(0, x2 - x1 + 1);
}
void run() {
	a[0].scan(); a[1].scan(); a[2].scan();
	for (int i = a[0].y[0]; i <= a[0].y[1]; ++i) {
		if (cross(i, i, a[1].y[0], a[1].y[1]) == 0 && cross(i, i, a[2].y[0], a[2].y[1]) == 0) 
			return out("YES");
	}
	for (int i = a[0].x[0]; i <= a[0].x[1]; ++i) { 
		int f = cross(i, i, a[1].x[0], a[1].x[1]), g = cross(i, i, a[2].x[0], a[2].x[1]);
		if (f && g) {
			continue;
		} else if (f) {
			if (cross(a[0].y[0], a[0].y[1], a[1].y[0], a[1].y[1]) != a[0].y[1] - a[0].y[0] + 1) return out("YES");	
		} else if (g) {
			if (cross(a[0].y[0], a[0].y[1], a[2].y[0], a[2].y[1]) != a[0].y[1] - a[0].y[0] + 1) return out("YES");	
		} else return out("YES");
	}
	out("NO");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	run();
	return 0;
}
