#include <bits/stdc++.h>
using namespace std;
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
      //  putc('\n');
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

typedef double db;
typedef long long ll;
const int N = 2e5 + 10;
struct Frac {
	ll x, y;
	void sim() {
		ll g = __gcd(x, y);
		x /= g;
		y /= g;
	}
	Frac() {}
	Frac(ll x, ll y) : x(x), y(y) { sim(); } 
	bool operator < (const Frac &other) const {
		return x * other.y < y * other.x;
	}
	bool operator == (const Frac &other) const {
		return x == other.x && y == other.y;
	}
};

struct Hash {
	Frac a[N]; int cnt;
	inline void init() { cnt = 0; } 
	inline void add(Frac x) { a[++cnt] = x; }
	inline void gao() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	inline int get(Frac x) { return lower_bound(a + 1, a + 1 + cnt, x) - a; }
}hx, hy;

inline ll sqr(ll x) {
	return x * x;
}
struct Point {
	int id;
	ll x, y;
	Frac arc[2];
	Point() {}
	Point(ll _x, ll _y, int _id = 0) {
		id = _id;
		x = _x;
		y = _y;
		arc[0] = arc[1] = Frac(0, 1);
	}
	inline ll len() {
		return sqr(x) + sqr(y);
	}
	inline ll operator ^ (const Point &other) const {
		return x * other.y - y * other.x;
	}
	inline ll operator * (const Point &other) const {
		return x * other.x + y * other.y;
	}
}o, tmp, o1;
struct node {
	int x, y, id;
	node() {}
	node(int x, int y, int id) : x(x), y(y), id(id) {}
	bool operator < (const node &other) const {
		if (x != other.x) return x < other.x;
		return y > other.y;
	}
};
vector <Point> vec[2]; 
vector <int> res[2];
vector <node> vv;
vector <vector<node>> ord;
int n, x[2], y[2], f[N]; 

inline void prework(vector<Point> &v) {
	for (auto &it : v) {
		tmp = Point(it.x - x[0], it.y - y[0]);
		it.arc[0] = Frac(sqr(tmp * o), (tmp.len() * o.len()));
		it.arc[0].x *= -1;
		tmp = Point(it.x - x[1], it.y - y[1]);
		it.arc[1] = Frac(sqr(tmp * o1), (tmp.len() * o1.len()));
		it.arc[1].x *= -1;
	}
}

struct BIT {
	int a[N], n;
	inline void init(int _n) { n = _n; memset(a, 0, sizeof (a[0]) * (n + 10)); }
	inline void update(int x, int v) {
		for (; x <= n; x += x & -x)
			a[x] = max(a[x], v);
	}
	inline int query(int x) {
		int res = 0;
		for (; x; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res; 
	}
}bit;

inline void gao(vector <int> &res, vector <Point> &v) {
	res.clear();
	if (v.empty()) return;
	hx.init(); hy.init();
	for (auto &it : v) {
		hx.add(it.arc[0]);
		hy.add(it.arc[1]);
	}
	hx.gao(); hy.gao();
	vv.clear();
	for (auto &it : v) {
		vv.push_back(node(hx.get(it.arc[0]), hy.get(it.arc[1]), it.id));
	}
	int n = hy.cnt;
	bit.init(n + 10);
	sort(vv.begin(), vv.end());
	int sze = vv.size(), Max = 0;
	for (int i = 0; i < sze; ++i) {
		f[i] = bit.query(vv[i].y - 1) + 1;
		bit.update(vv[i].y, f[i]);
		Max = max(Max, f[i]);
	}
	ord.clear(); ord.resize(Max + 1); 
	for (int i = 0; i < sze; ++i) {
		ord[f[i]].push_back(vv[i]);  
	}
	for (int i = Max; i >= 1; --i) {
		sort(ord[i].begin(), ord[i].end(), [&](node x, node y){
			return x.id < y.id;			
		});
		res.push_back(ord[i][0].id);
	}
}

inline bool small(vector <int> &vec1, vector <int> &vec2) {
	if (vec1.size() != vec2.size()) return vec1.size() > vec2.size();
	int sze = vec1.size();
	for (int i = 0; i < sze; ++i)
		if (vec1[i] != vec2[i]) {
			return vec1[i] < vec2[i];
		}
	return 1;
}

int main() {
	int _T; _T = read();
	for (int kase = 1; kase <= _T; ++kase) { 
		prints("Case #"); print(kase); prints(": "); 
		x[0] = read(); y[0] = read(); x[1] = read(); y[1] = read(); n = read(); 
		o = Point(x[1] - x[0], y[1] - y[0]);
		o1 = Point(x[0] - x[1], y[0] - y[1]);
		vec[0].clear(); vec[1].clear(); 
		for (int i = 1, x, y; i <= n; ++i) {
			x = read(); y = read();
			if ((o ^ (Point(x, y))) > 0) {
				vec[0].push_back(Point(x, y, i));
			} else {
				vec[1].push_back(Point(x, y, i));
			}
		}
		prework(vec[0]); prework(vec[1]);
		for (int i = 0; i < 2; ++i)
			gao(res[i], vec[i]);
		int id = 0;
		if (small(res[1], res[0])) id = 1;
		print(res[id].size()); putc('\n');
		for (auto &it : res[id]) print(it), putc('\n');
	}
	flush();
	return 0;
}
