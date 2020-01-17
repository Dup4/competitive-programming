#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline long long read() {
    long long tmp=0, fh=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') fh=-1; c=getchar();}
    while (c>='0'&&c<='9') tmp=tmp*10+c-48, c=getchar();
    return tmp*fh;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		ll n = read(), m = read(); 
		if (m * 2 < n) puts("Yes");
		else if (m % n == 0) puts("Yes");
		else if (m < n && n % (n - m) == 0) puts("No"); 
		else if (m > n) puts("No");
		else puts("Yes");
	}
	return 0;
}
