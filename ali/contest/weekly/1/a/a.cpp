#include <bits/stdc++.h>
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
constexpr int N = 1e5 + 10; 
int n; 

struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) {
		for (; x < N; x += x & -x)
			a[x] = max(a[x], v);
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x)
			res = max(res, a[x]);
		return res;
	}
}bit;

class Solution {
public:
    /**
     * @param meeting: the meetings
     * @param value: the value
     * @return: calculate the max value
     */

    int maxValue(vector<vector<int>> &meeting, vector<int> &value) {
        // write your code here
		int n = meeting.size();
		for (int i = 0; i < n; ++i) meeting[i].push_back(value[i]); 
		sort(meeting.begin(), meeting.end(), [&](vector<int> a, vector<int> b) { 
			if (a[0] == b[0]) return a[1] < b[1];
			return a[0] < b[0];
		});
		bit.init();
		ll res = 0;
		for (int i = 0; i < n; ++i) {
			ll f = bit.query(meeting[i][0]);
			f += meeting[i][2];
			bit.update(meeting[i][1], f);	
			res = max(res, f);
		}
		return res;
    }
};

void run() {
	rd(n);
	vector <vector<int>> meeting;
	vector <int> value(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		rd(x, y);
		vector <int> vec({x, y});
		meeting.push_back(vec);
	}
	for (auto &it : value) rd(it);
	pt((new Solution())->maxValue(meeting, value));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
