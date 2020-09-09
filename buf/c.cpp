#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5;
vector <vector<int>> fac;

int pri[N], check[N], mu[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else {
				mu[i * pri[j]] = -mu[i];
			}
		}
	}
}

ll f(int x) {
	ll res = 0;
	for (auto &it : fac[x]) {
		res += 
	}
}

ll g(int x) {

}

int main() {
	sieve();
	fac.clear();
	fac.resize(N + 5);
	for (int i = 1; i <= N; ++i) {
		for (int j = i; j <= N; j += i) {
			fac[j].push_back(i);
		}
	}
	for (int i = 1; i <= N; ++i) {
		assert(f(i) == g(i));
	}		
	return 0;	
}
