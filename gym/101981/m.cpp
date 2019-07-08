#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n, m;
char s[N], t[N];
int a[N];

char Ma[N << 1];
int Mp[N << 1], num[N << 1];
void add(int l, int r) {
	if (l > r) return;
	++num[l];
	--num[r + 1];
}
void Manacher(char *s, int len) {
	int l = 0;
	Ma[l++] = '$';
	Ma[l++] = '#';
	for (int i = 0; i < len; ++i) {
		Ma[l++] = s[i];
		Ma[l++] = '#';
	}
	Ma[l] = 0;
	int mx = 0, id = 0;
	for (int i = 0; i < l; ++i) {
		Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
		while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
		if (i + Mp[i] > mx) {
			mx = i + Mp[i];
			id = i;
		}
	}
	memset(a, 0, sizeof a);
	memset(num, 0, sizeof num);
	for (int i = 2; i < l; ++i) {
		if (isalpha(Ma[i])) {
			add(i + 2, i + Mp[i]);
		} else {
			add(i + 3, i + Mp[i]);	
		} 
	}
	for (int i = 2; i < l; ++i) {
		num[i] += num[i - 1];
		if (isalpha(Ma[i])) {
			a[i / 2 - 1] = num[i];		
		}
	}

	for (int i = 0; i < l; ++i) {
		printf("%2d ", i);
	}
	puts("");
	for (int i = 0; i < l; ++i) {
		printf("%2c ", Ma[i]);
	}
	puts("");
	for (int i = 0; i < l; ++i) {
		printf("%2d ", Mp[i]);
	}
	puts("");
	for (int i = 0; i < n; ++i) {
		printf("%2d ", a[i]);
	}
	puts("");
}

int nx[N];
void kmp_pre(char *x, int m, int *nx) {
	int i, j;
	j = nx[0] = -1;
	i = 0;
	while (i < m) {
		while (-1 != j && x[i] != x[j]) j = nx[j];
		nx[++i] = ++j; 
	}
}

ll KMP(char *x, int m, char *y, int n) {
	int i = 0, j = 0;
	ll res = 0;
	kmp_pre(x, m, nx);
	while (i < 2 * n) {
		while (-1 != j && y[i % n] != x[j]) j = nx[j];
		if (y[i % n] == x[j]) { 
			if (i < n) {
				++res;
			//	cout << i << " " << j << endl;
				res += 1ll * a[i - j];  
			} else {
				int pre = i - j;
				if (pre < n) {
					++res; 
			//		cout << i << " " << j << endl;
					res += 1ll * a[pre];
				}
			}
		}
		++i; ++j;
		if (j >= m) {
			j = nx[j];
		}
	}
	return res;
}

int main() {
	while (scanf("%s%s", s, t) != EOF) {
		n = strlen(s); m = strlen(t);
		reverse(s, s + n);
		Manacher(s, n);
		printf("%lld\n", KMP(t, m, s, n));	
	}
	return 0;
}
