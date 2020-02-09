#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
const int N = 1e6 + 10;
int n, a[N]; char s[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) a[i] = (s[i] - '0') * 9;
		reverse(a + 1, a + 1 + n);
		a[2] += a[1] / 10;
		a[1] %= 10;
		int x = 10 - a[1];
		++a[2];
		a[1] = 0;
		int digit_sum = 0;
		for (int i = 1; i <= n; ++i) {
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
			digit_sum += a[i];
		}
		if (a[n + 1] != 0) ++n;
		while (1) {
			if (digit_sum <= x) break;
			x += 10;
			++digit_sum;
			++a[2]; 
			for (int i = 2; i <= n; ++i) {
				if (a[i] < 10) break;
				digit_sum -= a[i + 1];
				a[i + 1] += a[i] / 10;
				digit_sum += a[i + 1]; 
				digit_sum -= a[i];
				a[i] %= 10;
			}
		}	
		printf("%d\n", x);
	}
	return 0;
}
