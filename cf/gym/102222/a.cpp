#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
#define uint unsigned int
const int N = 5e6 + 10;
int n, p, q, m;
uint SA, SB, SC;
pii sta[N]; int top;
ll res;
uint rng61() {
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	uint t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}

void push(int x) {
	if (top == 0) sta[++top] = pii(x, x);
	else {
		++top;
		sta[top] = pii(x, max(x, sta[top - 1].se));
	}
}

void pop() {
	if (top >= 1) --top;
}

void gen() {
	scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
	res = 0; top = 0; 
	for (int i = 1; i <= n; ++i) {
		if (int(rng61() % (p + q)) < p) {
			push(rng61() % m + 1);
		} else {
			pop(); 
		}
		if (top) {
			res ^= (1ll * i * sta[top].se);
		}
	}
	printf("%lld\n", res);
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		gen();
	}
	return 0;
}
