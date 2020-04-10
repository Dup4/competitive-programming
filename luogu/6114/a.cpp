#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;
char s[N];

vector<int> Duval(char *s) {
	vector <int> pos;
	for (int i = 0; s[i]; ) {
		int j = i, k = i + 1;
		for ( ; s[k] && s[k] >= s[j]; ++k) { 
			if (s[k] > s[j]) j = i;
			else ++j;
		}
		while (i <= j) {
			pos.push_back(i + k - j - 1);
			i += k - j;
		}
	}
	return pos;
}

int main() {
	scanf("%s", s);
	vector <int> pos(Duval(s));
	int res = 0;
	for (auto &it : pos) res ^= (it + 1);
	printf("%d\n", res);
	return 0;
}
