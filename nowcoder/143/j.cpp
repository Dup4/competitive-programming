#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, p2, p3;

ll DFS(int x) {
	if (x <= 0) {
		return 0;
	}
	return min(p2 + DFS(x - 2), p3 + DFS(x - 3));
} 

int main() {
	while (scanf("%lld%lld%lld", &n, &p2, &p3) != EOF) {
		ll res = p2 * (n / 2) + DFS(n % 2);
		res = min(res, p3 * (n / 3) + DFS(n % 3));
		res = min(res, (p2 + p3) * (n / 5) + DFS(n % 5)); 
		printf("%lld\n", res);	
	}
	return 0;
}
