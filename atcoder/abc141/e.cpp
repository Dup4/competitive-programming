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
constexpr int N = 5e3 + 10;
int n; char s[N];
typedef unsigned long long ull;
struct Hash {
	static ull base[N]; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * 131;  
	}
	ull a[N]; 
	inline void gao(char *s) { 
		a[0] = s[0];
		for (int i = 1; s[i]; ++i) {
			a[i] = a[i - 1] * 131 + s[i]; 
		}	
	}
	inline ull get(int l, int r) { 
		return a[r] - a[l - 1] * base[r - l + 1]; 
	}
}hs;
ull Hash::base[N] = {0};
void run() {
	cin >> (s + 1);
	hs.gao(s);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			int l = j - i, r = n - j + 1, pos = -1;
			while (r - l >= 0) {
				int mid = (l + r) >> 1;
				if (hs.get(i, i + mid - 1) == hs.get(j, j + mid - 1)) {
					pos = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			if (pos != -1) ans = max(ans, pos);
		}
	}
	cout << ans << endl;
}

int main() {
	Hash::init();
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
