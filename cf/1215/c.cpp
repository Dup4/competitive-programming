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
int n; char s[N], t[N];
vector <int> vec[2];
vector <pII> res;
void run() {
	vec[0].clear(); vec[1].clear();
	cin >> (s + 1) >> (t + 1);
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'a' && t[i] == 'b') vec[0].push_back(i);
		else if (s[i] == 'b' && t[i] == 'a') vec[1].push_back(i);
	}
	if ((vec[0].size() + vec[1].size()) & 1) return out(-1);
	res.clear();
	if (vec[0].size() & 1) {
		res.push_back(pII(vec[0].back(), vec[0].back()));
		vec[1].push_back(vec[0].back());
		vec[0].pop_back();
	}
	for (int i = 0, sze = vec[0].size(); i < sze; i += 2) {
		res.push_back(pII(vec[0][i], vec[0][i + 1]));
	}
	for (int i = 0, sze = vec[1].size(); i < sze; i += 2) {
		res.push_back(pII(vec[1][i], vec[1][i + 1]));
	}
	int sze = res.size();
	cout << sze << endl;
	for (auto &it : res) 
		cout << it.fi << " " << it.se << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
