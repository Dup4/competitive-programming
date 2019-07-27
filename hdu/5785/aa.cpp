#include <bits/stdc++.h>
using namespace std;

#define N 100010
int a[N], b[N];

int main() {
	memset(a, 0, sizeof a);
	a[1] += 1;
	a[11] -= 10;
	b[2] += 1;
	b[11] -= 1;
	for (int i = 1; i <= 20; ++i) {
		b[i] += b[i - 1];
		a[i] += a[i - 1] + b[i];
	}
	for (int i = 1; i <= 20; ++i) printf("%d%c", a[i], " \n"[i == 20]);
	return 0;
}
