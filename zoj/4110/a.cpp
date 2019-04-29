#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000010
char s[N], t[N];
char Ma[N << 1];
int Mp[N << 1], l;
void Manacher(char *s, int len) {
	l = 0;
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
}
bool ok(int l, int r) {
	for (int i = l, j = r; i <= r; ++i, --j) {
		if (s[i] != t[j]) {
			return false;
		}
	}
	return true;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		scanf("%s", t);
		if (strcmp(s, t) == 0) {
			Manacher(s, strlen(s));
			ll res = 0;
			for (int i = 0; i < l; ++i) {
				res += Mp[i] / 2;
			}
			printf("%lld\n", res);
		} else {
			int len = strlen(s);
			int l = -1, r = len;
			for (int i = 0; i < len; ++i) {
				if (s[i] != t[i]) {
					if (l == -1) {
						l = i;
					}
					r = i;
				}
			}
			if (ok(l, r)) {
				int res = 1;
				--l, ++r;
				while (l >= 0 && r < len) {
					if (s[l] != s[r]) {
						break;
					}
					++res;
					--l, ++r;
				}
				printf("%d\n", res);
			} else {
				puts("0");
			}
		}
	}
	return 0;
}
