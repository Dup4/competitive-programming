#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N];
vector <vector<int>> fac;

bool ok(int x) {
	for (auto it : fac[x]) {
		if (a[it]) return 1;
	}
	return 0;
}

int main() {
	fac.clear(); fac.resize(N);
	for (int i = 1; i < N; ++i) {
		for (int j = i + i; j < N; j += i) {
			fac[j].push_back(i);
		}
	}
	while (scanf("%d", &n) != EOF) {
		memset(a, 0, sizeof a); 
		int res = 0;	
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (i > 1) {
				if (!ok(x - 1)) {
					++res;
					a[x - 1] = 1;
				}
			}
		}
		printf("%d\n", res);
	}	
	return 0;
}
