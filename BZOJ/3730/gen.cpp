#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
inline int random(int a, int b) { return rnd() % (b - a + 1) + a; } 

int main() {
	int n = random(2, 100000), m = random(1, 5000);
	cout << n << " " << m << endl;
	for (int i = 1; i <= n; ++i) printf("%d%c", random(1, 10), " \n"[i == n]);
	for (int i = 2; i <= n; ++i) printf("%d %d\n", i, random(1, i - 1));  
	while (m--) {
		int op = random(0, 1);
		int x = random(1, n);
		int y = random(0, n - 1);
		printf("%d %d %d\n", op, x, y);
	}
	return 0;
}
