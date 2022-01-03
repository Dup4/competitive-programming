#include <bits/stdc++.h>
using namespace std;
#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define pii pair <int, int>
#define fi first
#define se second 
#define endl "\n" 
constexpr int N = 1e6 + 10;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y) { x += y; if (x >= mod) x -= mod; else if (x < 0) x += mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T > inline void out(T s) { cout << s << "\n"; }
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll qpow(ll base, ll n) { ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
int n, m, w, a[N];
ll S[N];
struct node { int l, r, a; }Sta[N]; int top;
inline void insert(int l, int r, int a) {
	if (!top) Sta[++top] = {l, r, a};
	else {
		while (top) {
			node &tmp = Sta[top];
			if (tmp.a > a) {
				l = tmp.r + 1; 
				break;
			}
			if (Sta[top].r < l) break;
			if (a >= tmp.a) {
				tmp.r = l - 1;
			}
			if (tmp.l > tmp.r) --top;
			else break; 
		}
		if (l <= r) {
			Sta[++top] = {l, r, a}; 
		}
	}
}
void run() {
	memset(S, 0, sizeof S);
	for (int i = 1; i <= n; ++i) {
		top = 0;
		cin >> m; 
		int add = w - m;  
		Sta[++top] = {1, add, 0}; 
		for (int j = 1; j <= m; ++j) cin >> a[j];  
		for (int j = 1; j <= m; ++j) {
			insert(j, min(w, j + add), a[j]);
		}
		insert(w - add + 1, w, 0); 
		for (int j = 1; j <= top; ++j) {
			S[Sta[j].l] += Sta[j].a;
			S[Sta[j].r + 1] -= Sta[j].a;
		} 
	}
	for (int i = 1; i <= w; ++i) {
		S[i] += S[i - 1];
		cout << S[i] << " \n"[i == w];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> w) run();
	return 0;
}
