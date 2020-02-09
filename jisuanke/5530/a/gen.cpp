#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }
int main() {
	int n = 10, m = 10;
	cout << n << " " << m << endl;
	for (int i = 1; i <= m; ++i) {
		int op = random(1, 5);
		int k = random(0, i - 1);
		int a = random(1, n);
		int b = random(1, n);
		if (op == 2 || op == 5) printf("%d %d %d\n", op, k, a);
		else printf("%d %d %d %d\n", op, k, a, b);
	}
	return 0;
}
