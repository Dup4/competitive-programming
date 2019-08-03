#include <bits/stdc++.h>
using namespace std;

struct node {
	int x;
	mutable int y;
	node() {}
	node(int x, int y) : x(x), y(y) {}
	bool operator < (const node &other) const {
		if (x != other.x)
			return x > other.x;
		return y < other.y;
	}
};

int main() {
	set <node> se;
	se.insert(node(1, 1));
	se.insert(node(2, 1));
	auto pos = se.lower_bound(node(2, 0));
	(*pos).y =3;
	for (auto it : se) {
		cout << it.x << " " << it.y << endl;
	}
	return 0;
}
