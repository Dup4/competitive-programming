#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n;

int main() {
	while (scanf("%lld", &n) != EOF) {
		printf("%lld\n", 7 + (1ll * n * (11 + n) >> 1));
	}
	return 0;
}
