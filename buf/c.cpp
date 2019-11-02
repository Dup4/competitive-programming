#include <bits/stdc++.h>
using namespace std;
using ll = long long;
char s[110];
bool ok() {
	
	for (int i = 0; i < 8; ++i) {
		
	}
}
void dfs(int cur) {
	if (cur == 8) {
		if (ok()) {
			s[8] = 0;
			printf("%s\n", s + 1);
			return;
		}
	}
	for (int i = '0'; i <= '9'; ++i) {
		s[cur] = i;
		dfs(cur + 1);
	}
}

int main() {
	dfs(0);
	return 0;
}
