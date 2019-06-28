#include <bits/stdc++.h>
using namespace std;

#define N 1000010
char s[N], t[N];

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		int lens = strlen(s + 1), lent = strlen(t + 1);
		int res = 0, Xor = 0, tot = 0;   
		for (int i = 1; i <= lent; ++i) { 
			if (s[i] != t[i]) {
				tot ^= 1;  
			}
			if (i > 1 && s[i] != s[i - 1]) Xor ^= 1; 
		}
		res += tot ^ 1;
		for (int i = lent + 1; i <= lens; ++i) {
			if (s[i] != s[i - 1]) Xor ^= 1; 
		    int pre = i - lent;
			if (pre > 1 && s[pre] != s[pre - 1]) Xor ^= 1;
			tot ^= Xor;
			res += tot ^ 1;	
		}
		printf("%d\n", res);
	}
	return 0;
}

