#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
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
constexpr int N = 2e5 + 10;  
int n, q, pre[N]; char s[N];

namespace Hash {
	ll base[N], seed = 131, mod = 1e9 + 7; 
	void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = (base[i - 1] * 131) % mod; 
	}
	struct ValNode { 
		ll val; int len;
		ValNode() { val = 0; len = 0; }
		ValNode(ll val, int len) : val(val), len(len) {}
		ValNode operator + (const ValNode &other) const {
			ValNode res = ValNode();
			res.len = len + other.len;
			res.val = val * base[other.len] + other.val;
			res.val %= mod;
			return res;
		}
	};
	ValNode one = ValNode(base[1] * '1', 1);
}

struct SEG {
	struct node {
		int pre, suf, cnt, len; 
		Hash::ValNode hashVal;
		node() { pre = suf = cnt = len = 0; hashVal = Hash::ValNode(); }
		void norm() {
			if (pre == len) {
				cnt = len / 2;
				if (len % 2) hashVal = Hash::one;
			} else {
				cnt += pre / 2;
				cnt += suf / 2;
				if (pre % 2) hashVal = Hash::one + hashVal;
				if (suf % 2) hashVal = hashVal + Hash::one;
			}
		}
		bool operator == (const node &other) const {
			node a = *this, b = other;
			a.norm(); b.norm();
			return a.cnt == b.cnt && a.hashVal.val == b.hashVal.val;
		}
		node operator + (const node &other) const {
			node res = node();
			res.len = len + other.len;
			res.pre = pre;
			if (pre == len) res.pre += other.pre;
			res.suf = other.suf;
			if (other.suf == other.len) res.suf += suf;
			res.cnt = cnt + other.cnt;
			if (pre != len && other.pre != other.len) {
				res.cnt += (suf + other.pre) / 2;
				res.hashVal = hashVal;
				if ((suf + other.pre) % 2) {
					res.hashVal = res.hashVal + Hash::one;
				}
				res.hashVal = res.hashVal + other.hashVal;
			} else if (pre != len) res.hashVal = hashVal;
			else if (other.pre != other.len) res.hashVal = other.hashVal;
			return res;
		}
		void print() { dbg(pre, suf, cnt, len, hashVal.val, hashVal.len); }
	}t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].pre = t[id].suf = (s[l] == '1'); 
			t[id].len = 1;
			t[id].hashVal = Hash::ValNode(Hash::base[1] * s[l], 1);
			return;	
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}	
	node query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(id << 1, l, mid, ql, qr);
		else if (ql > mid) return query(id << 1 | 1, mid + 1, r, ql, qr);
		else return query(id << 1, l, mid, ql, qr) + query(id << 1 | 1, mid + 1, r, ql, qr);	
	}
}seg;

int get(int l, int r) { return pre[r] - pre[l - 1]; }

void run() {
	cin >> (s + 1); 
	pre[0] = 0;
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + (s[i] == '1');
	}
	seg.build(1, 1, n);
	rd(q);
	while (q--) {
		static int l1, l2, cnt;
		rd(l1, l2, cnt);
		if ((get(l1, l1 + cnt - 1) == cnt && get(l2, l2 + cnt - 1) == cnt) ||
			(get(l1, l1 + cnt - 1) == 0 && get(l2, l2 + cnt - 1) == 0)) {
			pt("Yes");
			continue;
		}
	//	seg.query(1, 1, n, l1, l1 + cnt - 1).print();
	//	seg.query(1, 1, n, l2, l2 + cnt - 1).print();
		pt(seg.query(1, 1, n, l1, l1 + cnt - 1) == seg.query(1, 1, n, l2, l2 + cnt - 1) ? "Yes" : "No");
	}
}

int main() {
	Hash::init();
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
