#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

struct node {
	static int a[N];
	struct node2 {
		int x;
		bool operator < (const node2 &other) const {
			return a[x] < a[other.x];
		}
	};
};

int main() {
	return 0;
}
