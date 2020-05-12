#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	ll n; cin >> n;
	cout << (1ll << __builtin_popcountll(n)) << "\n";
	return 0;
}
