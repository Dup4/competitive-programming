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
const int N = 1e3 + 10;
int n; 
char s[N];

int ask(int x) {
	pt(x);
	cout.flush();
	int res; rd(res);
	return res;
}

void out() {
	s[n + 1] = 0;
	cout << (s + 1) << endl;
	cout.flush();
	string res; rd(res);
}

void flip() {
	for (int i = 1; i <= n; ++i)
		s[i] = ((s[i] - '0') ^ 1) + '0';
}

void run() {
	for (int i = 1; i <= n; ++i) s[i] = '0';
	for (int i = 1; i <= 5; ++i) {
		s[i] = ask(i) + '0';
		s[n - i + 1] = ask(n - i + 1) + '0'; 
	}
	if (n == 10) {
	//	for (int i = 1; i <= 10; ++i) {
	//		int x = ask(1);
	//	}
		return out();
	}
	int pos = 6;
	while (1) {
		int same = 1, samePos = -1, otherPos = -1;
		for (int i = 1; i < pos; ++i) {
			if (s[i] != s[n - i + 1])
				same = 0, otherPos = i;
			else 
				samePos = i;
		}	
		if (same) {
			int x = ask(samePos);
			x = ask(samePos); 
			if (x != (s[samePos] - '0')) {
				flip();	
			}
		} else {
			if (samePos != -1) {
				int x = ask(samePos);
				if (x != (s[samePos] - '0')) flip();
				x = ask(otherPos);
				if (x != (s[otherPos] - '0')) reverse(s + 1, s + 1 + n);	
			} else {
				int x = ask(1); x = ask(1);
				if (x != (s[1] - '0')) {
					reverse(s + 1, s + 1 + n);
				}	
			}
		}
		for (int i = 0; i < 4 && pos <= n / 2; ++i, ++pos) {
			s[pos] = ask(pos) + '0';
			s[n - pos + 1] = ask(n - pos + 1) + '0';
		}
		if (pos > n / 2) break;
	}
	out();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = nextInt(); rd(n);
	while (_T--) run(); 
//	while (cin >> n) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ":\n";
//        run();
//    }
	return 0;
}
