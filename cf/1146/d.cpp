#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define M 500000
int m, a, b;
int used[N], f;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
void DFS(int x, int up) {
	used[x] = 1;
	++f;
	if (x - b >= 0 && !used[x - b]) {
		DFS(x - b, up);
	}
	if (x + a <= up && !used[x + a]) {
		DFS(x + a, up); 
	}
}

int main() {
	while (scanf("%d%d%d", &m, &a, &b) != EOF) {
		memset(used, 0, sizeof used); 
		ll res = 0;
		used[0] = 1;
		f = 1;
		for (int i = 0; i <= min(m, M); ++i) {
			if (i >= a && used[i - a]) {
				DFS(i, i);
			}
			res += f;
		}
	
		if (m > M) {
			int g = gcd(a, b);
			
		}
		printf("%lld\n", res);
	}
	return 0;
}
