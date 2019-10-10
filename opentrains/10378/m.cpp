#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
using pss = pair<string, string>;
#define fi first
#define se second
const int N = 1e7 + 10;
const ll mod = 1ll << 31;
int a[N], n; ll seed;
BigNum res;
pss dfs(int u) {
	if (u > n) return pss("", "");
	int ls = u * 2, rs = u * 2 + 1;
	//0 up -> down 1 down -> up
	string l[2] = dfs(ls), r[2] = dfs(rs);
	
}


int main() {
	while (scanf("%d%lld", &n, &seed) != EOF) {
		res = BigNum("0");
		for (int i = 2; i <= n; ++i) {
			seed = (1ll * 1103515245 * seed + 12345) % mod;
			a[i] = ((seed >> 16) % 9) + 1;
		}
		dfs(1);
	}
	return 0;
}
