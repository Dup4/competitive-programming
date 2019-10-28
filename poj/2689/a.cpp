#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define ll long long
#define pLL pair<ll, ll>
#define fi first
#define se second
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
ll L, R;
int scheck[N], check[N];
ll pri[N]; int cp;
void sieve() {
	memset(scheck, 0, sizeof scheck);
	memset(check, 0, sizeof check);
	int limit = sqrt(R) + 1;
	scheck[1] = 1;
	if (L == 1) check[1] = 1;
	for (int i = 2; i <= limit; ++i) {
		if (scheck[i] == 0) {
			for (int j = 2; 1ll * i * j <= limit; ++j) {
				scheck[j * i] = 1;
			}
			for (ll j = max(2ll, (L + i - 1) / i); 1ll * i * j <= R; ++j) {
				check[1ll * i * j - L + 1] = 1;
			}
		}
	}
	cp = 0;
	for (int i = 1; i <= (R - L + 1); ++i) {
		if (check[i] == 0) {
			pri[++cp] = i + L - 1;
		}
	}
	if (cp <= 1) puts("There are no adjacent primes.");
	else {
		pLL ma = pLL(0, 0), mi = pLL(-INF, INF);
		for (int i = 2; i <= cp; ++i) {
			if (pri[i] - pri[i - 1] > ma.se - ma.fi) {
				ma = pLL(pri[i - 1], pri[i]);
			}
			if (pri[i] - pri[i - 1] < mi.se - mi.fi) {
				mi = pLL(pri[i - 1], pri[i]);
			}
		}
		printf("%lld,%lld are closest, %lld,%lld are most distant.\n", mi.fi, mi.se, ma.fi, ma.se);
	}
}

int main() {
	while (scanf("%lld%lld", &L, &R) != EOF) {
		sieve();
	}
	return 0;
}
