#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

struct node {
	ll x[2], y[2];
}arr[maxn];

int n;
map<vector<ll>, int> mp1;
map<vector<ll>, int> mp2;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		mp1.clear(), mp2.clear();
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld %lld %lld %lld", &arr[i].x[0], &arr[i].y[0], &arr[i].x[1], &arr[i].y[1]);
		}
		for (int i = 1; i <= n; ++i) {
			ll a = arr[i].y[0] - arr[i].y[1], b = arr[i].x[0] - arr[i].x[1];
			if (a == 0 || b == 0) {
				if (a || b) {
					a /= (a + b);
					b /= (a + b);
				}
			} else {
				ll g = gcd(a, b);
				a /= g, b /= g;
			}
			ll c = b * arr[i].y[0] - a * arr[i].x[0];
			vector<ll>v1 = {a, b};
			vector<ll>v2 = {a, b, c};
			res += n - i + mp2[v2] - mp1[v1];
			mp2[v2]++;
			mp1[v1]++;
		}
		printf("%lld\n", res);
	}
	return 0;
}
