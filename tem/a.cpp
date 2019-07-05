#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
char t[10002];
int n, m;
int comp(const void *p,const void *q){
    return(*(char *)q-*(char *)p);
}
char a[maxn];
char s[maxn];
int main() {
	int tt = 100;
	for (int i = 0; i < tt; ++i) {
		t[i] = 'a' + (i % 26);
	}
	qsort(t, tt, sizeof (char), comp);
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int k;
	while(scanf("%s%d",a,&k)!=EOF) {
		int len=strlen(a);
		int top=0;
		int res=0;
		int cnt=0;
		s[top++]=a[0];
		for(int i=1; i<len; i++) {
			if(a[i]!='0')
				while(top>0&&s[top-1]!='0'&&a[i]>s[top-1]&&res!=k) {
					top--;
					res++;
				}
			else {
				cnt++;
			}
			s[top++]=a[i];
		}
		int n=len-k-cnt;
		for(int i=0; i<top; i++) {
			if(s[i]=='0')
				printf("%c",s[i]);
			else if(n>0) {
				n--;
				printf("%c",s[i]);
			}
		}
		puts("");
	}
	return 0;
}
