#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
constexpr int N = 1e5 + 10; 
int n; 

bool valid(int n, int k, vector <int> target) {
	//pt(k);
	if (k == 0) return false;
	vector <int> vec(n);
	vector <int> res;
	for (int i = 0; i < n; ++i) vec[i] = i + 1;
	while (!vec.empty()) {
		vector <int> tmp[2];
		for (int i = 1; i <= SZ(vec); ++i) {
			tmp[i & 1].push_back(vec[i - 1]);
		}
		vec.clear();
		for (int i = 0; i < 2; ++i) {
			for (auto &it : tmp[i]) {
				vec.push_back(it);
			}
		}
		reverse(all(vec));
		int cnt = 0;
		while (cnt < k && !vec.empty()) {
			res.push_back(vec.back());
			vec.pop_back();
			++cnt;
		}
		reverse(all(vec));
	}
//	pt(res);
	return res == target;
}

class Solution {
public:
    bool isMagic(vector<int>& target) {
		int k = 0;
		n = SZ(target);
		vector <int> vec;
		for (int i = 2; i <= n; i += 2) vec.push_back(i);
	   	for (int i = 1; i <= n; i += 2) vec.push_back(i);
		for (int i = 0; i < n; ++i) {
			if (vec[i] == target[i])
				++k;
			else
				break;
		}	
	//	pt(k);
		return valid(n, k, target);

    }
};

void run() {
	int n; rd(n);
	vector <int> vec(n);
	for (auto &it : vec) rd(it);
	pt((new Solution())->isMagic(vec));

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
