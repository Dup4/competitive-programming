#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; while (x >= mod) x -= mod; while (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; } 
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e5 + 10;
int n, has[N], pri[N], mu[N], cnt[N];  
vector <vector<int>> fac;
void sieve() {
	int check[N];
	memset(check, 0, sizeof check);
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else {
				mu[i * pri[j]] = -mu[i]; 
			}
		}
	}
}

void update(int x, int v) {
	for (auto &it : fac[x])
		cnt[it] += v;
}
bool coprime(int x) {
	ll res = 0;
	for (auto &it : fac[x]) {
		res += mu[it] * cnt[it];
	}
	return res;
}

void run() {
	int Max = 1;
	memset(has, 0, sizeof has); 
	memset(cnt, 0, sizeof cnt);
	for (int i = 1, x; i <= n; ++i) has[x = rd()] = 1, chmax(Max, x);
	ll res = Max;
	for (int g = 1; g <= Max; ++g) {
		stack <int> sta;
		for (int i = Max / g; i >= 1; --i) {
			if (has[i * g] == 0) continue;
			while (coprime(i)) {
				chmax(res, 1ll * i * sta.top() * g);
				update(sta.top(), -1);
				sta.pop();
			}
			update(i, 1);
			sta.push(i);
		}
		while (!sta.empty()) {
			update(sta.top(), -1);
			sta.pop();
		}
	}
	pt(res);
}

int main() {
	fac.clear(); fac.resize(N);
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			fac[j].push_back(i);
		}
	}
	sieve();
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run();
	return 0;
}
