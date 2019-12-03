#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 10;
int pri[N], check[N]; ll phi[N];
void sieve() {
    memset(check, false, sizeof check);
    *pri = 0;
	phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (i * pri[j] >= N) break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            }
            else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
			}
		}
    }
	for (int i = 2; i < N; ++i) phi[i] += phi[i - 1];
}
 
int main() {
	sieve();
	int _T; cin >> _T;
	while (_T--) {
		int n; 
		scanf("%d", &n);
		printf("%lld\n", phi[n] * 2 - 1);
	}
    return 0;
}
