#include <bits/stdc++.h>
using namespace std;

#define ll long long
int n;

int main()
{
	ll res = 0; cin >> n;
	for (int i = 1; i <= n; ++i)
		res += n / i;
	cout << res << "\n";
	return 0;
}
