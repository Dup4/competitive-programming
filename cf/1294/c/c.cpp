#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> getfac(ll x) {
	vector <int> fac;
	for (int i = 2; 1ll * i * i <= x; ++i) {
		while (x % i == 0) {
			fac.push_back(i); 
			x /= i;
		}
	}	
	if (x != 1) fac.push_back(x); 
	return fac;
}

int n;

void gao() {
	vector <int> fac = getfac(n); 
	ll A = fac[0], B = 1, C = 1;
	if (fac.size() >= 2 && fac[1] != fac[0]) {
		B = fac[1];
		C = n / (A * B);
		if (C != 1 && A != B && A != C && B != C && A * B * C == n) {
			puts("YES");
			cout << A << " " << B << " " << C << "\n";
		} else {
			puts("NO");
		}
	} else if (fac.size() >= 3) {
		B = fac[1] * fac[2];
		C = n / (A * B);
		if (C != 1 && A != B && A != C && B != C && A * B * C == n) {
			puts("YES");
			cout << A << " " << B << " " << C << "\n";
		} else {
			puts("NO");
		}
	} else {
		puts("NO");
	}
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		gao();
	}
	return 0;
}
