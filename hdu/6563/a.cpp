#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m;
int a[N], b[N];
vector <int> A, B;

//打掉所有怪兽
ll f1() {
	ll res = 0;
	sort(B.begin(), B.end());
	multiset <int> se;
	for (int i = 1; i <= n; ++i) se.insert(a[i]);
	for (auto it : B) {
		auto pos = se.lower_bound(it);
		if (pos != se.end()) {
			se.erase(pos); 
		} else {
			return 0;
		}
	}
	sort(A.begin(), A.end());
	for (auto it : A) {
		if (se.empty() || *se.begin() < it) return 0;
		res += *se.begin() - it;  
		se.erase(se.begin());	
	}
	while (!se.empty()) {
		res += *se.begin();
		se.erase(se.begin());
	}
	return res;
}

//防御怪一个都不打
ll f2() {
	sort(A.begin(), A.end());
	ll res = 0;
	ll P = 0, Q = 0;
	int id = n;
	int Move = 1e9;
	for (auto it : A) {
		int pos = upper_bound(A.begin(), A.end(), a[id]) - A.begin();
		Move = min(Move - 1, pos + 1);
		if (Move <= 0) break;
		P += a[id]; --id;
		Q += it;
		res = max(res, P - Q); 
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		scanf("%d%d", &n, &m);
		printf("Case %d: ", kase);
		A.clear(); B.clear();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			x == 0 ? 
				A.push_back(b[i]):
				B.push_back(b[i]);
		}
		sort(a + 1, a + 1 + n);
		ll res = max(f1(), f2());
		printf("%lld\n", res);
	}
	return 0;
}
