#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)x.size())
#define L(i,u) for (register int i=head[u]; i; i=nxt[i])
#define rep(i,a,b) for (register int i=(a); i<=(b); i++)
#define per(i,a,b) for (register int i=(a); i>=(b); i--)
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef pair<int,int> Pii;
typedef vector<int> Vi;
template<class T> inline void read(T &x){
	x=0; char c=getchar(); int f=1;
	while (!isdigit(c)) {if (c=='-') f=-1; c=getchar();}
	while (isdigit(c)) {x=x*10+c-'0'; c=getchar();} x*=f;
}
template<class T> inline void umin(T &x, T y){x=x<y?x:y;}
template<class T> inline void umax(T &x, T y){x=x>y?x:y;}
inline ui R() {
	static ui seed=613;
	return seed^=seed>>5,seed^=seed<<17,seed^=seed>>13;
}
const int N = 266666,mo=1e9+7,bas=300007,M=5550000;
inline void add(int &x, int y){x=x+y<mo?x+y:x+y-mo;}
inline void sub(int &x, int y){x=x-y>=0?x-y:x-y+mo;}
int mi[N],n,a[N],l[N],r[N],p[N];ll k;

int lc[M],rc[M],val[M],cnt[M],tot,rt[N];
void ins(int &k, int K, int p, int l, int r){
	k=++tot,lc[k]=lc[K],rc[k]=rc[K],val[k]=val[K],cnt[k]=cnt[K];
	if(l==r){cnt[k]++;val[k]=(val[k]+mi[l])%mo;return;}
	int mid=(l+r)>>1;
	if(p<=mid)ins(lc[k],lc[K],p,l,mid);
	else ins(rc[k],rc[K],p,mid+1,r);
	val[k]=(val[lc[k]]+val[rc[k]])%mo;
}
int qry(int k1, int k2, int k3, int k4, int l, int r){
//	if((val[k2]-val[k1]+mo)%mo==(val[k4]-val[k3]+mo)%mo)return 0;
	if(l==r)return cnt[k2]-cnt[k1]>cnt[k4]-cnt[k3];
	int mid=(l+r)>>1;
//	int c=val[lc[k2]];sub(c,val[lc[k1]]);sub(c,val[lc[k4]]);add(c,val[lc[k3]]);if(c)
	if((1ll*(val[lc[k2]]-val[lc[k1]])-(val[lc[k4]]-val[lc[k3]]))%mo)
		return qry(lc[k1],lc[k2],lc[k3],lc[k4],l,mid);
	return qry(rc[k1],rc[k2],rc[k3],rc[k4],mid+1,r);
}
bool cmp(int l1, int r1, int l2, int r2){
	if((val[rt[r1]]-val[rt[l1-1]]+mo)%mo==(val[rt[r2]]-val[rt[l2-1]]+mo)%mo)
		return l1<l2;
	return qry(rt[l1-1],rt[r1],rt[l2-1],rt[r2],1,1e5);
}
int main() {//freopen("1.in","r",stdin);freopen("1.out","w",stdout);

	mi[0]=1;rep(i,1,N-1)mi[i]=1ll*mi[i-1]*bas%mo;
	read(n);read(k);
	rep(i,1,n)read(a[i]),l[i]=i,r[i]=n;
	rep(i,1,n)ins(rt[i],rt[i-1],a[i],1,1e5);
//	printf("%d\n",cmp(1,2,3,3));
//	printf("%d\n",cmp(1,3,1,3));
//	printf("%d\n",cmp(1,3,1,2));
//	printf("%d\n",cmp(3,4,1,2));
	while(1){
		ll tot=0;rep(i,1,n)if(l[i]<=r[i])tot+=r[i]-l[i]+1;
		ll tmp=(19260817ll*R()+233ll*R()+R())%tot+1;//1..tot
		int L,R;
	//	rep(i,1,n)printf("%d:%d %d\n",l[i],r[i]);
		rep(i,1,n)if(l[i]<=r[i]){
			if(tmp>r[i]-l[i]+1)tmp-=r[i]-l[i]+1;
			else{L=i;R=l[i]+tmp-1;break;}
		}
	//	assert(L&&L<=R);
	//	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
		ll gengxiao=0;
		int cc=0;rep(i,1,n)if(l[i]<=r[i]){int x=r[i]-l[i]+1;while(x)cc++,x>>=1;}
	if(cc<=1.5*n){	
		rep(i,1,n)if(l[i]<=r[i]){
			int zuo=l[i],you=r[i];p[i]=r[i]+1;
			while(zuo<=you){
				int mid=(zuo+you)>>1;
				if(cmp(i,mid,L,R))p[i]=mid,you=mid-1;else zuo=mid+1;
			}
			gengxiao+=r[i]-p[i]+1;
		}
	}
	else{
		for(int i=n,j=n+1;i>=1;i--){
			while(j-1>=i&&cmp(i,j-1,L,R))j--;
			if(l[i]<=r[i])p[i]=max(min(j,r[i]+1),l[i]),gengxiao+=r[i]-p[i]+1;
		}
	}
		//cerr<<tot<<' '<<k<<' '<<gengxiao<<' '<<L<<' '<<R<<endl;
		if(gengxiao+1==k){
			sort(a+L,a+R+1);
			rep(i,L,R)printf("%d%c",a[i], " \n"[i == R]);
			return 0;
		}
		if(gengxiao+1<k){
			rep(i,1,n)if(l[i]<=r[i])r[i]=p[i]-1;k-=gengxiao+1;
			r[L]=R-1;
		}
		else{
			rep(i,1,n)if(l[i]<=r[i])l[i]=p[i];
		}
	}
	return 0;
}
