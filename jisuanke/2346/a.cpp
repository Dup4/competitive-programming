#include <bits/stdc++.h>
using namespace std;

#define N 5010
int n;
vector < vector <int> > G;
int d[N];  

int main() {
	while (scanf("%d", &n) != EOF) {
		G.clear();
		G.resize(n + 1);
		memset(d, 0, sizeof d);
		int Max = 0;
		for (int i = 1, x, y; i < n; ++i) {
			scanf("%d%d", &x, &y);
			G[x].push_back(y);
			G[y].push_back(x);  
			++d[x]; ++d[y]; 
			Max = max(Max, d[x]);
			Max = max(Max, d[y]);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (d[i] == Max) {
				res += d[i];
				d[i] = 0;
				for (auto it : G[i]) {
					--d[it];
				}
				break;
			}
		}
		Max = *max_element(d + 1, d + 1 + n);
		printf("%d\n", Max + res - 1);
		
	}
	return 0;
}
