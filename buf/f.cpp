#include <bits/stdc++.h>
using namespace std;

bool __slp__x__;
template <typename T>
struct HULL {
	T INF = 1e9;
	struct node {
		T slp, x, y;
		node(T _slp = 0, T _x = 0, T _y = 0) : slp(_slp), x(_x), y(_y) {}
		bool operator < (const node &other) const { return __slp__x__ ? slp > other.slp : x < other.x; }
		T operator - (const node &other) const { return (y - other.y) / (x - other.x); }
	};
	set <node> Q;
	void init() { Q.clear(); }
	void add(T x, T y) {
		__slp__x__ = 0;
		node t(0, x, y);
		typename set<node>::iterator it = Q.lower_bound(node(0, x, 0));
		if (it != Q.end()) {
			if ((it->x == x && it->y >= y) || (it->x != x && it->slp <= *it - t)) return;
			if (it->x == x) Q.erase(it);
		}
		it = Q.insert(t).first;
		typename set<node>::iterator it3 = it; it3--;
		while (it != Q.begin()) {
			typename set<node>::iterator it2 = it3;
			if (it2 != Q.begin() && t - *it2 >= *it2 - *--it3) Q.erase(it2);
			else break;
		}
		it3 = it; it3++;
		while (it3 != Q.end()) {
			typename set<node>::iterator it2 = it3;
			if (++it3 != Q.end() && *it2 - *it3 >= *it2 - t) Q.erase(it2);
			else break;
		}
		if (it == Q.begin()) const_cast<T&>(it->slp) = INF;
		else {
			typename set<node>::iterator it2 = it; it2--;
			const_cast<T&>(it->slp) = t - *it2;	
		}
		typename set <node>::iterator it2 = it; it2++;
		if (it2 != Q.end()) const_cast<T&>(it2->slp) = t - *it2;
	}
	T get(T a, T b) {
		//max(ax + by)
		if (Q.empty()) return INF;
		__slp__x__ = 1;
		typename set<node>::iterator it = Q.lower_bound(node(-a / b, 0, 0));
		if (it != Q.begin()) it--;
		return it->x * a + it->y * b;
	}
};

int main() {
	HULL <long long> hull;
	hull.add(1, 3);
	hull.add(3, 4);
	hull.add(-100, 100);
	cout << hull.get(1, 100) << endl;
	return 0;
}
