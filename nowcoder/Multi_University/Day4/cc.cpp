#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 3000010
int n, a[N];
ll b[N], res;

struct Cartesian_Tree {
	struct node {
		int id, val, fa; ll Min[2], Max[2], sum; 
		int son[2];
		node() {} 
		node (int id, int val, int fa, ll Min, ll Max) : id(id), val(val), fa(fa), w(w), Min(Min), Max(Max) {
			son[0] = son[1] = 0;
		}
	}t[N];
	int root;
	pii b[N];
	void init() {
		t[0] = node(0, -1e9, 0);
	}
	void build(int n, int *a, ll *b) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0, b[i], b[i]);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[k].val > t[i].val) {
				k = t[k].fa;
			}
			
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i; 
		}
		root = t[0].son[1];
	}
	int DFS(int u) {
		if (!u) return 0;
		return lsze + rsze + 1;  lsze +  
	}
}CT; 

namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    inline void reads(char *s)
    {
        char c=Get();int tot=0;
        while(c<'a'||c>'z') c=Get();
        while(c>='a'&&c<='z') s[++tot]=c,c=Get();
        s[++tot]='\0';
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
		putc('\n');
    }
    inline void prints(const char *s)
    {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}using namespace IO;

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	b[0] = 0;
	for (int i = 1; i <= n; ++i) {
		b[i] = read();
		b[i] += b[i - 1]; 
	}
	res = -INFLL;
	CT.init();
	CT.build(n, a);
	CT.DFS(CT.root);
	printf("%lld\n", res);
	return 0;
}
