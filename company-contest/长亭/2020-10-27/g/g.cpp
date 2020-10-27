#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, m, a[N];

int main() {
	scanf("%d%d", &n, &m);
	priority_queue <int, vector<int>, greater<int>> pq;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	m = min(n, m);
	for (int i = 1; i <= m; ++i) {
		pq.push(a[i]);
	}
	for (int i = m + 1; i <= n; ++i) {
		int x = pq.top(); pq.pop();
		x += a[i];
		pq.push(x);
	}
	int x = pq.top();
	printf("%d\n", x + 1);
	return 0;
}
