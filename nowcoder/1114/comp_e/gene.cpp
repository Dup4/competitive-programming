#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	int n = 5, q = 5;
	cout << n << " " << q << endl;
	for (int i = 1; i <= n; ++i) printf("%d%c", rnd() % 10, " \n"[i == n]);
	for (int i = 1, l, r; i <= q; ++i) {
		l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r) swap(l, r);
		printf("%d %d\n", l, r);
	}
	return 0;
}
