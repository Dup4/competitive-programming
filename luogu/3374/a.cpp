#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 10;
int n, q;
ll a[N];
struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) {
		for (; x < N; x += x & -x) 
			a[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x & -x) 
			res += a[x];
		return res;
	}
	ll query(int l, int r)
}bit;

int main() {
	while (scanf("%d%d", &n, &q) != EOF) {
		
	}
	return 0;
}
