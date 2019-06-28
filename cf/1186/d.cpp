#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;
char s[110];
int a[N], b[N], c[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		int can = 0;
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s + 1);
			a[i] = 0, b[i] = 0;
			int j = 1, len = strlen(s + 1);
			int f = 1;
		    if (s[1] == '-') ++j, f = -1; 	
			for (; j <= len && s[j] != '.'; ++j) {
				a[i] = a[i] * 10 + s[j] - '0';
			}
			for (++j; j <= len; ++j) {
				b[i] = b[i] * 10 + s[j] - '0';
			}
			a[i] *= f;
			if (f == -1) {
				++can;
				if (a[i] < 0) {
					--a[i];
				}
			}
			sum += a[i];
		}
		sum = abs(sum);
	    //assert(sum <= can); 	
		for (int i = 1; i <= n; ++i) {
			if (sum > 0 && b[i] != 0) {
				++a[i];
				--sum;
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d\n", a[i]);
		}	
	}
	return 0;
}
