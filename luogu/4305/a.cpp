#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, a[N];

namespace IO {
	const int S = (1 << 20) + 5;
    //Input Correlation
    char buf[S], *H, *T;
    inline char gc() {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		return H == T ? ' ' : *H++;
    }
	inline bool blank(char ch) {
	  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
  	template <class T>
	inline void read(T &x) {
	  register double tmp = 1;
	  register bool sign = 0;
	  x = 0;
	  register char ch = gc();
	  for (; !isdigit(ch); ch = gc())
	    if (ch == '-') sign = 1;
	  for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
	  if (ch == '.')
	    for (ch = gc(); isdigit(ch); ch = gc())
	      tmp /= 10.0, x += tmp * (ch - '0');
	  if (sign) x = -x;
	}
    inline void read(char *s) {
 		register char ch = gc();
 		for (; blank(ch); ch = gc());
 		for (; !blank(ch); ch = gc()) *s++ = ch;
 		*s = 0;
 	}
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[110];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void write(I x) { 
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
	template <class I> inline void writeln(I x) { write(x); putc('\n'); }
    inline void writes(const char *s) {
        int len=strlen(s);
        for(int i=0;i<len;i++) putc(s[i]);
        putc('\n');
    }
    inline void writed(int d,double x) {
        long long t=(long long)floor(x);
        write(t);putc('.');x-=t;
        while(d--) {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
    }
}

template <class T>
struct HashMap {  // 哈希表模板
	static const int SZ = 999997;
	struct data {
    	T u;
    	int v, nex;
  	};                // 前向星结构
  	data e[SZ << 1];  // SZ 是 const int 表示大小
  	int h[SZ], cnt;
  	int hash(T u) { return u % SZ; }
  	int& operator[](T u) {
    	int hu = hash(u);  // 获取头指针
    	for (int i = h[hu]; i; i = e[i].nex)
			if (e[i].u == u) return e[i].v;
    	return e[++cnt] = (data){u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  	}
	void init() { cnt = 0; memset(h, 0, sizeof h); }
};
HashMap <int> hashMap;

unordered_map <int, int> mp;

int main() {
	int _T; IO::read(_T);
	while (_T--) {
		mp.clear();
		IO::read(n);
		*a = 0;
		for (int i = 1, x; i <= n; ++i) {
			IO::read(x);
			if (mp[x] == 0) {
				a[++*a] = x;
				mp[x] = 1;
			}
		}
		for (int i = 1; i <= *a; ++i) {
			IO::write(a[i]);
			IO::putc(" \n"[i == *a]);
		}
	}
	IO::flush();
	return 0;
}
