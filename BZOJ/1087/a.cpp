#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, k, limit, dis[N * 10], OFFSET; 

void dfs(int x, int step) {
	if (step > dis[x + OFFSET] || step > limit)
		return;
	dis[x + OFFSET] = step;
	if (x > k) {
		if (step + x - k <= limit) {
			dis[k + OFFSET] = min(dis[k + OFFSET], step + x - k);
		}
		return;
	}
	if (x * 2 > k) dfs(x - 1, step + 1);
	if (x < k) dfs(x + 1, step + 1); 
	if (x < k * 2) dfs(x * 2, step + 1); 
}

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		OFFSET = N * 2;
		if (n == k) {
			puts("0");
			continue;
		}
		memset(dis, 0x3f, sizeof dis);
		for (limit = 1; ;++limit) {
			dfs(n, 0);
			if (dis[k + OFFSET] != INF) {
				printf("%d\n", limit);
				break;
			}
		}
	}
	return 0;
}
