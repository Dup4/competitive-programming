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
constexpr int N = 1e6 + 10; 
int n, m, q; char s[N], t[N]; 

struct DEQUE { 
	char que[N << 1];
    int	head, tail, rev;
	void init() { head = N, tail = N - 1, rev = 0; }
	void push(char ch) {
		if (rev) que[--head] = ch;
		else que[++tail] = ch;
	}
	char pop() {
		char ch;
		if (rev == 0) {
			ch = que[head++];
		} else {
			ch = que[tail--];
		}
		return ch;
	}
	char get(int pos) {
		if (rev == 0) return que[head + pos - 1];
		else return que[tail - pos + 1];
	}
}deq;

void run() {
	cin >> (s + 1);
	deq.init();
	int l = 1, r = m;
	for (int i = 1; i <= r; ++i) deq.push(s[i]);
	string res = "";
	while (q--) {
		int op, pos;
		rd(op, pos);
		if (op == 2) {
			if (pos < l || pos > r) res += s[pos];
			else res += deq.get(pos - l + 1);
		} else {
			while (l < pos) {
				s[l] = deq.pop();
				deq.push(s[r + 1]);
				++l; ++r;
			}
			deq.rev ^= 1;
		}
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> q) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
