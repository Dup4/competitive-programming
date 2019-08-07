#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 220010
const int p = 1e9 + 7;
ll f[N][1 << 9][1 << 9]; 
int n, a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		f[0][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; 
		}
	}
	return 0;
}
