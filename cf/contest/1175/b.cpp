#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define ll long long
ll limit = (1ll << 32); 
ll res, base;
bool F;
int cnt[110];
int Sta[N], top;
void add() {
	if (!F) {
		return;
	}
	ll base = 1;
	for (int i = 100; i > 1; --i) {
		for (int j = 1; j <= cnt[i]; ++j) {
			base *= i;
			if (base >= limit) {
				F = 0;
				break;
			}
		}
	}
	res += base;
	if (res >= limit) {
		F = 0;
	}
}

int main() {
	F = 1; res = 0; 
	memset(cnt, 0, sizeof cnt);
	char op[10]; int n;   	
	int q; scanf("%d", &q); 
	while (q--) {
		scanf("%s", op + 1);
		if (op[1] == 'f') {
			scanf("%d", &n);
			Sta[++top] = n;
			++cnt[n];
		} else if (op[1] == 'e') {
			--cnt[Sta[top]];
			--top;
		} else {
			add();	
		}
	}
	if (!F) puts("OVERFLOW!!!"); 
	else {
		printf("%lld\n", res); 
	}
	return 0;
}
