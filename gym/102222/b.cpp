#include <bits/stdc++.h>

using namespace std;

typedef double db;

#define N 210

struct node {
	db x, y;

	node () {}

	node (db _x, db _y) {
		x = _x;
		y = _y;
	}

	void input() {
		scanf("%lf %lf", &x, &y);
	}

	node operator - (const node &other) const {
		return node(x - other.x, y - other.y);
	}

	db len() {
		return hypot(x, y);
	}

	db operator * (const node &other) const {
		return x * other.x + y * other.y;
	}
}p[N], o;

int n;

int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		printf("Case #%d: ", cas);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			p[i].input();
			p[i + n] = p[i];
		}
		o.input();
		db res = 0.0;
		for (int i = 0; i < n; ++i) {
			db len = (o - p[i + 1]).len();
			node a = p[i + 1] - p[i];
			node b = p[i + 2] - p[i + 1];
			db theta = acos((a * b) / (a.len() * b.len()));
			res += theta * len;
		}
		printf("%.3f\n", res);
	} 
	return 0;	
}
