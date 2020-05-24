#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
#define endl "\n" 
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
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
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e7 + 10; 
int n, a[N], f[N], g[N]; 

struct splitmix64_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

hash_map <int, int> mp; 

//unordered_map <int, int> mp;

vector <int> vec;

void run() {
	rd(n);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	mp.clear();
	mp[0] = 1;
	ll res = 0;
	int Max = 0, now = 0;
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i - 1] + a[i];
		now += a[i];
		chmax(Max, now);
		if (now < 0) now = 0;
		if (i <= ceil(sqrt(Max))) {
			for (int j = 0; j < i; ++j) {
				if (f[i] - f[j] >= 0 && g[f[i] - f[j]]) ++res;
			}
		} else {
			for (auto &it : vec) {
				if (it > Max) break;
				int x = f[i] - it;
				res += mp[x];
			//	if (mp.count(x)) res += mp[x];
			}
		}
		++mp[f[i]];
	}
	pt(res);
}

int main() {
	for (int i = 0; i * i <= 1e7; ++i) {
		int x = i * i;
		g[x] = 1;
		vec.push_back(x);
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt();
//	while (_T--) run(); 
    for (int kase = 1; kase <= _T; ++kase) {
        cout << "Case #" << kase << ": ";
        run();
    }
//	while (cin >> n) run();
//	run();
	return 0;
}
