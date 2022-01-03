#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, mod = 1e7 + 7;
int n, pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

int main() {
	int num = 0;
	for (int i = 1; i <= 120; ++i) if (120 % i == 0) cout << i << endl, ++num;
	int tot = 0;
	for (int i = 1; i <= num; ++i) if (num % i == 0) tot += i;
	cout << num << " " << tot << endl;
	sieve();
	while (scanf("%d", &n), n) {
			
	}
	return 0;
}
