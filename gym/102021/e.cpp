#include <bits/stdc++.h>
using namespace std;

const int N = 2e7 + 10;
int a, b, g, pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	check[1] = 1; 
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
int rd() {
	char s[20]; 
	scanf("%s", s); 
	int a = 0, b = 0, cnt = 0;
	bool F = 0;
	for (int i = 0; s[i]; ++i) {
		if (s[i] == '.') {
			F = 1;
		} else if (!F) {
			a = a * 10 + s[i] - '0';
		} else {
			++cnt;
			b = b * 10 + s[i] - '0';
		}
	}
	cnt = 5 - cnt;
	while (cnt--) b = b * 10;
	return a * 100000 + b;
}

int main() {
	sieve();
	int _T; cin >> _T;
	while (_T--) {
		a = rd(), b = rd();
	//	cout << a << " " << b << endl;
		g = __gcd(a, b);
		a /= g, b /= g;
		if (a == 1 && b == 1) a = b = 2;
		if (!check[a] && !check[b]) printf("%d %d\n", a, b); 
		else puts("impossible");	
	}
	return 0;
}
