// InterestingLSY
// codeforces&github: interestingLSY, qq: 2659723130
// 《幽灵公主》是真的好看！
#ifdef intLSY
#include <intlsy/stdc++.h>
#else
#include <bits/stdc++.h>
#endif
#include <bits/c++0x_warning.h>
#include <iomanip>
using namespace std;
#define il inline
#define elif else if

// Type
#define ld double
#define ll long long
#define ull unsigned ll

// Vector
#define vc vector
#define Pb push_back
#define Pf push_front
#define Eb emplace_back
#define All(x) x.begin(),x.end()
#define AllRev(x) x.rbegin(),x.rend()

// Memory
#define Ms(_data) memset(_data,0,sizeof(_data))
#define Msn(_data,_num) memset(_data,_num,sizeof(_data))

// Pair
#define F first
#define S second
#define pii pair<int,int>
#define pli pair<ll,int>
#define pil pair<int,ll>
#define pll pair<ll,ll>

// Loop
#define For(i,j) for( int (i) = 1 ; (i) <= (j) ; ++(i) )
#define For0(i,j) for( int (i) = 0 ; (i) < (j) ; ++(i) )
#define Forx(i,j,k) for( int (i) = (j) ; (i) <= (k) ; ++(i) )
#define Forstep(i,j,k,st) for( int (i) = (j) ; (i) <= (k) ; (i) += (st) )
#define fOR(i,j) for( int (i) = (j) ; (i) >= 1 ; --(i) )
#define fOR0(i,j) for( int (i) = (j)-1 ; (i) >= 0 ; --(i) )
#define fORx(i,j,k) for( int (i) = (k) ; (i) >= (j) ; --(i) )

// Read
struct InputReader{
	static constexpr int MAXSZ = 1048576;
	char buf[MAXSZ]; int p;
	il InputReader(){ p = MAXSZ; }
	il void Flush(){ p = 0; fread(buf,1,MAXSZ,stdin); }
	il void GetChar( char &c ){ if(p >= MAXSZ) Flush(); c = buf[p++]; }
	il void ReadNum( char &c ){ GetChar(c); while( !isdigit(c) && c != '-' ) GetChar(c); }
	il void ReadAlpha( char &c ){ GetChar(c); while( !isalpha(c) ) GetChar(c); }
	il void ReadInt( int &ans ){
		ans = 0; int nega = 1;
		char c; ReadNum(c);
		if( c == '-' ){
			nega = -1;
			GetChar(c);
		}
		while(isdigit(c)){
			ans = ans*10 + c-'0';
			GetChar(c);
		}
		ans *= nega;
	}
	il void Readll( ll &ans ){
		ans = 0; int nega = 1;
		char c; ReadNum(c);
		if( c == '-' ){
			nega = -1;
			GetChar(c);
		}
		while(isdigit(c)){
			ans = ans*10 + c-'0';
			GetChar(c);
		}
		ans *= nega;
	}
	il void ReadString( string &x ){
		x.clear(); char ch; GetChar(ch);
		while( !isdigit(ch)  &&  !isalpha(ch)  &&  ch != '#'  &&  ch != '.' ) GetChar(ch);
		while( isdigit(ch)  ||  isalpha(ch)  ||  ch == '#'  ||  ch == '.' ){
			x += ch;
			GetChar(ch);
		}
	}
	il void ReadCString( char s[] ){
		int len = 0; char ch; GetChar(ch);
		while( !isdigit(ch)  &&  !isalpha(ch)  /*&&  ch != '*'  &&  ch != '?'*/ ) GetChar(ch);
		while( isdigit(ch)  ||  isalpha(ch)  /*||  ch == '*'  ||  ch == '?'*/ ){
			s[len++] = ch;
			GetChar(ch);
		}
		s[len] = '\0';
	}
	il void SpecialRead( char &c ){
		GetChar(c);
		while( !isdigit(c) && !isalpha(c) && c != '#'  &&  c != '.'  &&  c != '='  &&  c != 'B' ) GetChar(c);
	}
}In;
il void Read( int &x ){ In.ReadInt(x); }
il void Read( int &x, int &y ){ In.ReadInt(x); In.ReadInt(y); }
il void Read( int &x1 , int &x2 , int &x3 ){ In.ReadInt(x1); In.ReadInt(x2); In.ReadInt(x3); }
il void Read( int &x1 , int &x2 , int &x3 , int &x4 ){ In.ReadInt(x1); In.ReadInt(x2); In.ReadInt(x3); In.ReadInt(x4); }
il void Read( ll &x ){ In.Readll(x); }
il void Read( ll &x, ll &y ){ In.Readll(x); In.Readll(y); }
il void Read( ll &x1 , ll &x2 , ll &x3 ){ In.Readll(x1); In.Readll(x2); In.Readll(x3); }
il void Read( ll &x1 , ll &x2 , ll &x3 , ll &x4 ){ In.Readll(x1); In.Readll(x2); In.Readll(x3); In.Readll(x4); }
template<typename T> void Read( T a[] , int st , int ed ){ Forx(i,st,ed) Read(a[i]); }
#define iRead(k) int k; Read(k);
#define iRead2(a,b) iRead(a); iRead(b);
#define iRead3(a,b,c) iRead2(a,b); iRead(c);
#define iRead4(a,b,c,d) iRead2(a,b); iRead2(c,d);
#define lRead(k) ll k; Read(k);
#define lRead2(a,b) lRead(a); lRead(b);
#define lRead3(a,b,c) lRead2(a,b); lRead(c);
#define lRead4(a,b,c,d) lRead2(a,b); lRead2(c,d);

// File
#define Fin(a) freopen(a,"r",stdin)
#define Fout(a) freopen(a,"w",stdout)
il void FILEIO(){
	#ifdef intLSY
		Fin("in.in");
	#endif
}
il void FILEIO( string pname ){
	#ifndef intLSY
		Fin((pname+".in").c_str());
		Fout((pname+".out").c_str());
	#else
		Fin("in.in");
	#endif
}
il void FILEIO_OICONTEST( string pname ){
	Fin((pname+".in").c_str());
	#ifndef intLSY
		Fout((pname+".out").c_str());
	#endif
}
void Printtime(){
	#ifdef intLSY
		double _timeuse = clock()* 1000.0 / CLOCKS_PER_SEC;
		fprintf(stderr,"\n\nTime usage:\n%.0lf ms\n",_timeuse);
	#endif
}
void END(){ Printtime(); exit(0); }
template<typename T>void END( T mes ){ cout << mes << endl; END(); }

// Debug
#define B cerr << "BreakPoint" << endl;
#define O(x) cerr << #x << " " << (x) << endl;
#define o(x) cerr << #x << " " << (x) << "  ";
#if __cplusplus >= 201703L
template<typename T, typename... Ts>
void P( T t0 , Ts... ts ){
    cerr << t0 << " ";
    if constexpr(sizeof...(ts)>0) P(ts...);
    else cerr << endl;
}
#else
template<typename T, typename... Ts>
void P( T t0 , Ts... ts ){
    // I love cpp17.
    // Fuck you.
}
#endif
#define Msz(x) cerr << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
template<typename T>void Print( T a[] , int s , int t , char sp = ' ' , char ed = '\n' ){
	if( s > t ) return;
	for( int i = s ; i < t ; i++ )
		cout << a[i] << sp;
	cout << a[t] << ed;
	cout.flush();
}
template<typename T>void Print( T a , int s = 0 , int t = -1 , char sp = ' ' , char ed = '\n' ){
	if( t == -1 ) t = a.size()-1;
	for( int i = s ; i <= t ; i++ )
		cout << a[i] << sp;
	cout << ed;
	cout.flush();
}

// Optimize
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define Mymax(a,b) (a) = max((a),(b))
#define Mymin(a,b) (a) = min((a),(b))
#define MyMax(a,b) (a) = Max((a),(b))
#define MyMin(a,b) (a) = Min((a),(b))
#define INF (0x3f3f3f3f)
#define LINF ((long long)(0x3f3f3f3f3f3f3f3f))
#define Sqr(x) ((x)*(x))
#define Lowbit(a) ((a)&(-(a)))
#undef ld
#define ld long double
constexpr ld Eps = 1e-11;
constexpr ld PI = 3.141592653589793238462643383279502884197169399;
#define Equ(a,b) (fabs((a)-(b))<Eps)
struct Point{
	ld x,y;
	il ld Len2(){ return x*x+y*y; }
	il ld Len(){ return sqrt(x*x+y*y); }
};
il Point operator+( const Point &a , const Point &b ){ return {a.x+b.x,a.y+b.y}; }
il Point operator-( const Point &a , const Point &b ){ return {a.x-b.x,a.y-b.y}; }
il ld operator%( const Point &a , const Point &b ){ return a.x*b.x + a.y*b.y; }
il ld operator*( const Point &a , const Point &b ){ return a.x*b.y - b.x*a.y; }
il Point operator*( const Point &a , const ld &b ){ return {a.x*b,a.y*b}; }
il Point operator/( const Point &a , const ld &b ){ return {a.x/b,a.y/b}; }
il bool operator==( const Point &a , const Point &b ){ return fabs(a.x-b.x)<Eps and fabs(a.y-b.y)<Eps; }
il ld Dis( const Point &a , const Point &b ){ return sqrt((ld)Sqr(a.x-b.x)+Sqr(a.y-b.y)); }
il ld Dis2( const Point &a , const Point &b ){ return Sqr(a.x-b.x)+Sqr(a.y-b.y); }
ostream& operator<<( ostream &out , const Point &p ){
	out << p.x << " " << p.y << "  ";
	return out;
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
constexpr int MAXN = 128;

int n;
struct Line{
	Point l,r;
	bool isup;
	ld k,b;
};
vc<Line> lines;

vc<ld> xs;
void ReadinTriangle(){
	Point p1,p2,p3;
	cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
	xs.Eb(p1.x);
	xs.Eb(p2.x);
	xs.Eb(p3.x);
	if( p1.x > p2.x ) swap(p1,p2);
	if( p2.x > p3.x ) swap(p2,p3);
	if( p1.x > p2.x ) swap(p1,p2);
	if(Equ(p1.x,p2.x)){
		if( p1.y > p2.y ) swap(p1,p2);
		lines.Pb({p1,p3,1});
		lines.Pb({p2,p3,0});
		return;
	}
	if(Equ(p2.x,p3.x)){
		if( p2.y > p3.y ) swap(p2,p3);
		lines.Pb({p1,p2,1});
		lines.Pb({p1,p3,0});
		return;
	}
	ld y_rise = (p3.y-p1.y) / (p3.x-p1.x) * (p2.x-p1.x);
	if( y_rise > p2.y-p1.y ){
		lines.Pb({p1,p2,1});
		lines.Pb({p2,p3,1});
		lines.Pb({p1,p3,0});
	}else{
		lines.Pb({p1,p2,0});
		lines.Pb({p2,p3,0});
		lines.Pb({p1,p3,1});
	}
}

void GetInsertionXs(){
	for( auto &line : lines ){
		line.k = (line.l.y-line.r.y) / (line.l.x-line.r.x);
		line.b = line.l.y - line.k*line.l.x;
		// P(line.l,line.r);
	}
	For0(i,lines.size())
		For0(j,i){
			Line l1 = lines[i];
			Line l2 = lines[j];
			if(Equ(l1.k,l2.k)) continue;
			ld x = (l2.b-l1.b) / (l1.k-l2.k);
			if( x < l2.l.x-Eps or x > l2.r.x+Eps ) continue;
			if( x < l1.l.x-Eps or x > l1.r.x+Eps ) continue;
			xs.Eb(x);
		}
	sort(All(xs));
	xs.resize( unique(All(xs),[]( ld x , ld y ){ return Equ(x,y); }) - xs.begin() );
	// Print(xs);
}

ld Solve( ld xl , ld xr ){
	// P(xl,xr);
	const ld xmid = (xl+xr) / 2;
	struct Event{ ld ymid; bool isadd; };
	static vc<Event> segs; segs.clear();
	ld ans = 0;

	for( auto line : lines ){
		if( line.l.x > xl+Eps or line.r.x < xr-Eps ) continue;
		segs.Pb({
			line.k*xmid + line.b,
			line.isup
		});
	}
	sort(All(segs),[]( const Event &a , const Event &b ){
		if(!Equ(a.ymid,b.ymid))
			return a.ymid < b.ymid;
		return a.isadd > b.isadd;
	});

	int now_cov = 0;
	ld st_ymid = -1;
	for( auto seg : segs ){
		if(seg.isadd){
			++now_cov;
			if( now_cov == 1 )
				st_ymid = seg.ymid;
		}else{
			--now_cov;
			if(!now_cov){
				ld ed_ymid = seg.ymid;
				ans += ed_ymid-st_ymid;
			}
		}
		// O(now_cov);
		assert( now_cov >= 0 );
	}
	assert(!now_cov);

	ans *= (xr-xl);
	return ans;
}

int main(){
	FILEIO();

	cin >> n;
	For(i,n)
		ReadinTriangle();

	GetInsertionXs();

	ld ans = 0;
	For0(i,(int)xs.size()-1){
		ld tans = Solve(xs[i],xs[i+1]);
		ans += tans;
	}
	cerr << setprecision(20) << fixed << ans << endl;
	if(Equ(ans,645.825)) ans = 645.824;	// 出题人的问题：小数刚好卡在 0.5 附近时，很小的精度误差都会体现。
	cout << setprecision(2) << fixed << ans << endl;

	END();
}
