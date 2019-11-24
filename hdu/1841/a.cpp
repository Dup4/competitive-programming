#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], t[N];

struct ExKMP {
	int Next[N];
	int extend[N];
	//下标从1开始
	void get_Next(char *s) {
		int lens = strlen(s + 1), p = 1, pos;
		//Next[1]要特殊考虑
		Next[1] = lens;
		while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
		//Next[2]初始化
		Next[pos = 2] = p - 1;
		for (int i = 3; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			//第一种情况
			if (len + i < p + 1) Next[i] = len;
			//第二种情况
			else {
				//找到对于子串最靠后已经匹配的位置
				int j = max(p - i + 1, 0);
				//暴力匹配
				while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
				p = i + (Next[pos = i] = j) - 1; 
			}
		}
	}

	void work(char *s, char *t) {
		get_Next(t);
		int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
		while (p <= lent && s[p] == t[p]) ++p;
		p = extend[pos = 1] = p - 1;
		for (int i = 2; i <= lens; ++i) {
			int len = Next[i - pos + 1];
			if (len + i < p + 1) extend[i] = len;
			else {
				int j = max(p - i + 1, 0);
				while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
				p = i + (extend[pos = i] = j) - 1;
			}
		}
	}
}exkmp;

int gao(char *s, char *t) {
	int lens = strlen(s + 1), lent = strlen(t + 1);
	exkmp.work(s, t);
	for (int i = 1; i <= lens; ++i) {
		if (exkmp.extend[i] == lent) return lent;
		if (exkmp.extend[i] == lens - i + 1) {
			return lens - i + 1;
		}
	}
	return 0;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s%s", s + 1, t + 1);
		int lens = strlen(s + 1), lent = strlen(t + 1);
		int Max = max(gao(s, t), gao(t, s));
		printf("%d\n", lens + lent - Max);	
	}
	return 0;
}