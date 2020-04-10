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

const int SIZE = 1000000;
const int M = 999997;
struct HashTable {
  struct Node {
    int next, value, key;
  } data[SIZE];
  int head[M], size;
  void init() { size = 0; memset(head, 0, sizeof head); }
  int f(int key) { return key % M; }
  int get(int key) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value;
    return -1;
  }
  int modify(int key, int value) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value = value;
  }
  int add(int key, int value) {
    if (get(key) != -1) return -1;
    data[++size] = (Node){head[f(key)], value, key};
    head[f(key)] = size;
    return value;
  }
};
HashTable hashTable;

int main() {
	int _T; IO::read(_T);
	while (_T--) {
		hashTable.init();
		IO::read(n);
		*a = 0;
		for (int i = 1, x; i <= n; ++i) {
			IO::read(x);
			if (hashTable.add(x, 1) != -1) {
				a[++*a] = x;
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
