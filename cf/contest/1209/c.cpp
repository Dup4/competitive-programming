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
constexpr int N = 2e5 + 10;
int n, a[N], b[N]; char s[N];
bool gao(int x) {
	int pre[2] = {0, 0};
	for (int i = 1; i <= n; ++i) {
	//	if (x == 4) cout << i << endl;
		if (a[i] < x) {
			if (pre[0] && a[i] < a[pre[0]]) return 0;
			b[i] = 1;
			pre[0] = i;
		} else if (a[i] == x) {
			if (pre[1] == 0 || a[i] >= a[pre[1]]) {
				b[i] = 2;
				pre[1] = i;
			} else {
				b[i] = 1;
				pre[0] = i;
			} 
		} else {
			if (pre[1] && a[i] < a[pre[1]]) return 0;
			b[i] = 2;
			pre[1] = i;
		}
	}
	return 1;
}
void run() {
	cin >> n >> (s + 1);
	for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
//	for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];
	for (int i = 0; i <= 9; ++i) {
		if (gao(i)) {
		//	cout << n << " " << i << endl;
			for (int j = 1; j <= n; ++j) cout << b[j];
			cout << endl;
			return;
		}
	}
	out("-");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T; cin >> _T;
	while (_T--) run();
	return 0;
}
