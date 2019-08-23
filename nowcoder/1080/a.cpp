#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int main() {
	int pre[N];
	int n; string s;
	cin >> n >> s;
	memset(pre, -1, sizeof pre);
	for (int i = 0; i < n; ++i) {
		if (pre[s[i] - 'a'] != -1 && pre[s[i] - 'a'] < i - 1) {
			puts("NO");
			exit(0);
		}
		pre[s[i] - 'a'] = i;
	}
	puts("YES");	
	return 0;
}
