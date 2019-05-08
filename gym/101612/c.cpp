#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N];
int mp[220], id[220];
char fid[220];
int link[220][220]; 

void File() {
	freopen("consonant.in", "r", stdin);
	freopen("consonant.out", "w", stdout);	
}
int main() {
	File();
	mp['a'] = 1;
	mp['e'] = 1;
	mp['i'] = 1;
	mp['o'] = 1;
	mp['u'] = 1;
	mp['w'] = 1;
	mp['y'] = 1;
	int cnt = 0;
	for (int i = 'a'; i <= 'z'; ++i) if (!mp[i]) {
		id[i] = cnt++;
		fid[cnt] = i;
	}
	while (scanf("%s", s + 1) != EOF) {
		memset(link, 0, sizeof link); 
		int len = strlen(s + 1);
		for (int i = 2; i <= len; ++i) {
			if (mp[s[i]] == 0 && mp[s[i - 1]] == 0) {
				++link[id[s[i - 1]]][id[s[i]]]; 
			} 
		}
		int res = 0;
		int Max = 0;
		for (int i = 0; i < (1 << 19); ++i) { 
			int tmp = 0;
			for (int j = 0; j < 19; ++j) {
				for (int k = 0; k < 19; ++k) {
					if (((i >> j) & 1) != ((i >> k) & 1)) {
						tmp += link[k][j];
					}
				}
			}
			if (tmp > Max) {
				Max = tmp;
				res = i;
			}
		}
		for (int i = 1; i <= len; ++i) {
			char c = s[i];
			int pos = id[c];
			if ((res >> pos) & 1) {
				c -= 32;
			}
			putchar(c);
		}
		puts("");
	}
	return 0;
}
