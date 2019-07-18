#include <bits/stdc++.h>
using namespace std;

#define N 400010
#define S_unit 15010
int n, a[N], res[N];
vector <vector<int>> vec;
map <int, int> mp; int cnt_id;
int getid(int x) {
	if (mp.find(x) == mp.end()) {
		return mp[x] = cnt_id++;
	}
	return mp[x];
}

#define db double
const db PI = acos(-1.0);
struct Complex {
	db x, y;
	Complex(db _x = 0.0, db _y = 0.0) {
		x = _x;
		y = _y;
	}
	Complex operator - (const Complex &b) const {
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex &b) const {
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex &b) const {
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
}x1[N], x2[N];

void change(Complex *y, int len) {
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; ++i) {
		if (i < j) swap(y[i], y[j]);
		k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}

void fft(Complex *y, int len, int on) {
	change(y, len);
	for (int h = 2; h <= len; h <<= 1) {
		Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
		for (int j = 0; j < len; j += h) {
			Complex w(1, 0);
			for (int k = j; k < j + h / 2; ++k) {
				Complex u = y[k];
				Complex t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1) {
		for (int i = 0; i < len; ++i) {
			y[i].x /= len;
		}
	}
}

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
}

void read(int &x) {
	x = 0; char ch;
	while (!isdigit(ch = getchar()));
	while (isdigit(ch)) {
		x = x * 10 - '0' + ch;
		ch = getchar();
	}
}

void out(int x) {
	if (x / 10) out(x / 10);
	putchar(x % 10 + '0');
}

void init() {
	for (int i = 1; i <= n; ++i) res[i] = 0;
	vec.clear();
	vec.resize(n + 10);
	cnt_id = 0;
	mp.clear();
}
int main() {
	int T = IO::read();
	while (T--) {
		n = IO::read();
		init();
		vec[getid(0)].push_back(0);
		int len = 1;
		while (len < (2 * n + 1)) len <<= 1;
		for (int i = 1; i <= n; ++i) {
			a[i] = IO::read();
			a[i] ^= a[i - 1];
			vec[getid(a[i])].push_back(i);
		}
		for (int i = 0; i < cnt_id; ++i) {
			int sze = (int)vec[i].size();
			if (1ll * sze * sze <= 2ll * n * log(2 * n) / log(2)) {
				for (register int j = 1; j < sze; ++j) {
					for (register int k = 0; k < j; ++k) {
						++res[vec[i][j] - vec[i][k]]; 
					}
				}
			} else {
				for (int i = 0; i < len; ++i) {
					x1[i] = Complex(0, 0);
					x2[i] = Complex(0, 0);
				}
				for (auto it : vec[i]) {
					x1[it] = Complex(1, 0);
					x2[n - it] = Complex(1, 0);
				}
				fft(x1, len, 1);
				fft(x2, len, 1);
				for (int i = 0; i < len; ++i) {
					x1[i] = x1[i] * x2[i];
				}
				fft(x1, len, -1);
				for (int i = n; i <= 2 * n; ++i) {
					res[i - n] += (int)(x1[i].x + 0.5);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", res[i], " \n"[i == n]);
		}
	//	for (int i = 1; i <= n; ++i) {
	//		IO::print(res[i]); IO::flush();
	//		putchar(" \n"[i == n]);
	//	}
	}
	return 0;
}
