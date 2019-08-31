#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
struct Point {
	int id;  
	ll x, y;
	Point() {}
	Point(ll _x, ll _y, int _id = 0) {
		id = _id;
		x = _x;
		y = _y;
	}
	inline ll operator ^ (const Point &other) const {
		return x * other.y - y * other.x;
	}
}o[2], tmp[2];
struct node {
	Point arc[2];
	int id, a, b; 
	node() {}
	node(Point arc1, Point arc2, int id) {
		arc[0] = arc1;
		arc[1] = arc2;
		this->id = id;
		a = b = 0;
	}
};
bool cmp1(node &x, node &y) {
	return (x.arc[0] ^ y.arc[0]) < 0;
}
bool cmp2(node &x, node &y) {
	return (x.arc[0] ^ y.arc[0]) > 0;
}
bool cmp3(node &x, node &y) {
	return (x.arc[1] ^ y.arc[1]) < 0; 
}
bool cmp4(node &x, node &y) {
	return (x.arc[1] ^ y.arc[1]) > 0; 
}
vector <Point> vec[2];
vector <node> vv;
vector <int> res[2];
vector <vector<int>> ord;
int n, x[2], y[2], f[N]; 

inline void prework(vector<Point> &v) {
	vv.clear();
	for (auto &it : v) {
		tmp[0] = Point(it.x - x[0], it.y - y[0]);
		tmp[1] = Point(it.x - x[1], it.y - y[1]);
		vv.push_back(node(tmp[0], tmp[1], it.id));
	}
}

struct BIT {
	int a[N], n;
	inline void init(int _n) { n = _n; memset(a, 0, sizeof (a[0]) * (n + 10)); }
	inline void update(int x, int v) {
		for (; x <= n; x += x & -x)
			a[x] = max(a[x], v);
	}
	inline int query(int x) {
		int res = 0;
		for (; x; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res; 
	}
}bit;

inline void gao(vector <int> &res) {
	res.clear();
	if (vv.empty()) return; 
	int F, sze = vv.size();
	if ((vv[0].arc[1] ^ o[1]) < 0) F = 0;
	else F = 1;
	sort(vv.begin(), vv.end(), (F ? cmp3 : cmp4)); 
	vv[0].b = 1;
	for (int i = 1; i < sze; ++i) {
		if ((vv[i].arc[1] ^ vv[i - 1].arc[1]) == 0) vv[i].b = vv[i - 1].b;
		else vv[i].b = vv[i - 1].b + 1;
	}
	if ((vv[0].arc[0] ^ o[0]) < 0) F = 0;
	else F = 1;
	sort(vv.begin(), vv.end(), (F ? cmp1 : cmp2)); 
	vv[0].a = 1;
	for (int i = 1; i < sze; ++i) {
		if ((vv[i].arc[0] ^ vv[i - 1].arc[0]) == 0) vv[i].a = vv[i - 1].a;
		else vv[i].a = vv[i - 1].a + 1;
	}
	sort(vv.begin(), vv.end(), [&](node x, node y){
		if (x.a != y.a) return x.a < y.a;
		return x.b > y.b; 		
	});
	bit.init(n); 
	int Max = 0;	
	for (int i = 0; i < sze; ++i) {
		f[i] = bit.query(vv[i].b - 1) + 1;
		bit.update(vv[i].b, f[i]); 
		Max = max(Max, f[i]);  
	}
	ord.clear(); ord.resize(Max + 10); 
	for (int i = 0; i < sze; ++i) {
		ord[f[i]].push_back(i); 
	}
	int pos = sze;
	for (int i = Max; i >= 1; --i) {
		int now = -1;
		for (auto &it : ord[i]) {
			if (pos == sze || (vv[it].a < vv[pos].a && vv[it].b < vv[pos].b)) {
				if (now == -1 || vv[it].id < vv[now].id) {
					now = it;
				}
			}
		}
		pos = now;
		res.push_back(vv[now].id);
	}
}

inline bool small(vector <int> &vec1, vector <int> &vec2) {
	if (vec1.size() != vec2.size()) return vec1.size() > vec2.size();
	int sze = vec1.size();
	for (int i = 0; i < sze; ++i)
		if (vec1[i] != vec2[i]) {
			return vec1[i] < vec2[i];
		}
	return 1; 
}

int main() {
	int _T; cin >> _T;
	for (int kase = 1; kase <= _T; ++kase) { 
		printf("Case #%d: ", kase);
		scanf("%d%d%d%d%d", x, y, x + 1, y + 1, &n);
		o[0] = Point(x[1] - x[0], y[1] - y[0]);
		o[1] = Point(x[0] - x[1], y[0] - y[1]);
		vec[0].clear(); vec[1].clear();  
		for (int i = 1, X, Y; i <= n; ++i) {
		    scanf("%d%d", &X, &Y); 	
			if ((o[0] ^ (Point(X - x[0], Y - y[0]))) > 0) { 
				vec[0].push_back(Point(X, Y, i));
			} else {
				vec[1].push_back(Point(X, Y, i));
			}
		}
		for (int i = 0; i < 2; ++i) {
			prework(vec[i]);
			gao(res[i]);
		}
		if (small(res[1], res[0])) swap(res[0], res[1]); 
		printf("%d\n", (int)res[0].size());
		for (auto &it : res[0]) printf("%d\n", it);
	}
	return 0;
}
