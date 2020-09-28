#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7; 
ll n, a, b; 

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%lld%lld", &n, &a, &b);
		printf("%lld\n", gao(n)); 
	}
	return 0;
}
