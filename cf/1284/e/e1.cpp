#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n" 
using namespace std;
using db = long double;
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

const db eps = 1e-16;
const db PI = acos(-1.0L); 
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

struct Point {
	db x, y;
	Point(db x = 0, db y = 0) : x(x), y(y) {}
	void scan() { rd(x, y); }
	void print() { pt(x, y); }
	bool operator == (const Point &b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
	Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	Point operator * (const db &b) const { return Point(x * b, y * b); }
	Point operator / (const db &b) const { return Point(x / b, y / b); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	db operator * (const Point &b) const { return x * b.x + y * b.y; }
	db len() { return norm(complex<db>(x, y)); }
	db len2() { return x * x + y * y; }
	db dis(Point b) { return norm(complex<db>(x - b.x, y - b.y)); }
	db dis2(Point b) { return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y); }
	int quad() {
		int _x = sgn(x), _y = sgn(y);
		if (_x > 0 && _y >= 0) return 1;
		if (_x <= 0 && _y > 0) return 2;
		if (_x < 0 && _y <= 0) return 3;
		if (_x >= 0 && _y < 0) return 4;
	}
	//求PA和PB构成的夹角 lightOJ 1203
	db getRad(Point a, Point b) {
		Point p = *this;
		return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
	}
	//单位法向量
	Point normal() { return Point(-y, x) / len(); }
	//化为长度为r的向量
	Point trunc(db r) {
		db l = len();
		if (!sgn(l)) return *this;
		r /= l;
		return Point(x * r, y * r);
	}
	//逆时针旋转90度
	Point rotleft() { return Point(-y, x); }
	//顺时针旋转90度
	Point rotright() { return Point(y, -x); }
	//绕点p旋转rad弧度
	Point rotate(Point p, db rad) {
		Point v = (*this) - p;
		db c = cos(rad), s = sin(rad);
		return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
	}
};

int n; 

ll C(int n, int m) {
	if (n < m) return 0;
	ll res = 1;
	for (int i = n; i > n - m; --i) res = res * i;
	for (int i = 2; i <= m; ++i) res = res / i;
	return res;
}

void run() {
	vector <Point> vec(n);
	for (int i = 0; i < n; ++i) vec[i].scan();
	ll res = C(n, 5) * 5;
	for (int i = 0; i < n; ++i) {
		vector <db> tmp;
		for (int j = 0; j < n; ++j) if (i != j) {
			tmp.push_back(atan2(vec[i].y - vec[j].y, vec[i].x - vec[j].x));
			if (sgn(tmp.end()[-1]) < 0) tmp.end()[-1] += PI * 2;
		}	
		sort(tmp.begin(), tmp.end());
		for (int j = 0; j < n - 1; ++j) tmp.push_back(tmp[j] + PI * 2);
		int r = 1;
		for (int l = 0; l < n - 1; ++l) {
			while (fabs(tmp[r] - tmp[l]) < PI) ++r;
			res -= C(r - l - 1, 3);
		}
	}	
	pt(res);
}

int main() {
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
