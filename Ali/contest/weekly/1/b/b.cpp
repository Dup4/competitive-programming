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

void dfs(vector<pair<int, vector<int>>> mem[], vector<int>& ref, int digits, int cur, int idx) {
    if (idx == digits) {
        vector<int> dcur;
        for (int c = cur; c; c /= 10) dcur.push_back(c % 10);
        reverse(dcur.begin(), dcur.end());
        mem[digits].push_back({cur, dcur});
    } else if (idx == 0) {
        for (int i = 1; i <= 9; i++)
            dfs(mem, ref, digits, cur * 10 + i, idx + 1);
    } else {
        int pos = idx - (digits - (int)ref.size());
        int diff = pos >= 0 ? ref[pos] : 0;
        int last = cur % 10;
        if (diff == 0)
            dfs(mem, ref, digits, cur * 10 + last, idx + 1);
        else {
            for (int sign : {-1, 1}) {
                int val = last + diff * sign;
                if (val < 0 || val > 9) continue;
                else dfs(mem, ref, digits, cur * 10 + val, idx + 1);
            }
        }
    }
}

const int maxdigits = 9;
vector<pair<int, vector<int>>> luckies[maxdigits + 1];
vector<int> lucky_nums;

void gao() {
	luckies[1].push_back({7, {7}});
	for (int digits = 2; digits <= maxdigits; digits++)
	    for (int i = 1; i <= digits - 1; i++)
	        for (auto& ref : luckies[i])
	            dfs(luckies, ref.second, digits, 0, 0);
	
	for (int digits = 1; digits <= maxdigits; digits++)
	    for (auto& v : luckies[digits])
	        lucky_nums.push_back(v.first);
	sort(lucky_nums.begin(), lucky_nums.end());
}

class Solution {
public:
    /**
     * @param l: left
     * @param r: right
     * @return: return the number of lucky number in [l,r]
     */
	int f = 0;
	void init() {
		f = 1;
		gao();
	}
    int theNumberofLuckyNumber(int l, int r) {
    	// write your code here
		if (!f) init();
		auto pr = upper_bound(lucky_nums.begin(), lucky_nums.end(), r);
	    auto pl = upper_bound(lucky_nums.begin(), lucky_nums.end(), l - 1);
	    return pr - pl;
    }
};

void run() {
	int l, r;
	rd(l, r);
	pt((new Solution())->theNumberofLuckyNumber(l, r));
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
