
#include <bits/stdc++.h>
using namespace std;

struct node {
	int x, y;
	node (int x) {
		this->x = x;
		int t = x;
		y = 0;
		for (int i = 2; i < x; ++i) if (t % i == 0) {
			++y;
			while (t % i == 0) {
				t /= i;
			}
		}
		//cout << x << " " << y << endl;
	}
	bool operator < (const node &other) const {
		if (y != other.y) {
			return y < other.y;
		}
		return x < other.x;
	}
};

int main() {
	int m; cin >> m;
	multiset <node> se;
	for (int i = 1, x; i <= m; ++i) {
		for (int j = 1; j <= 10; ++j) {
			scanf("%d", &x);
			se.insert(node(x));
		}
		cout << (*se.rbegin()).x << " " << (*se.begin()).x << endl;
		se.erase(--se.end());
		se.erase(se.begin());
	}
	return 0;
}
