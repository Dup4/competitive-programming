#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define SZ 666666
int MOD; ll w[2][SZ],G,fac[SZ],rfac[SZ];
inline ll qp(ll a,ll b)
{
    ll ans=1; a%=MOD;
    while(b)
    {
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return ans;
}
inline ll org_root()
{
    static ll yss[2333];
    int yyn=0; ll xp=MOD-1;
    for(ll i=2;i*i<=xp;i++)
    {
        if(xp%i) continue;
        yss[++yyn]=i;
        while(xp%i==0) xp/=i;
    }
    if(xp!=1) yss[++yyn]=xp;
    ll ans=1;
    while(1)
    {
        bool ok=1;
        for(int i=1;i<=yyn;i++)
            if(qp(ans,(MOD-1)/yss[i])==1) {ok=0; break;}
        if(ok) return ans; ++ans;
    }
}
int K; ll rv;
inline void fftinit(int n)
{
    for(K=1;K<n;K<<=1);
    w[0][0]=w[0][K]=1;
    ll g=qp(G,(MOD-1)/K);
    for(int i=1;i<K;i++) w[0][i]=w[0][i-1]*g%MOD;
    for(int i=0;i<=K;i++) w[1][i]=w[0][K-i];
    rv=qp(K,MOD-2);
}
inline void fft(int* x,int v)
{
    for(int i=0;i<K;i++) (x[i]<0)?(x[i]+=MOD):0;
    for(int i=0,j=0;i<K;i++)
    {
        if(i>j) swap(x[i],x[j]);
        for(int l=K>>1;(j^=l)<l;l>>=1);
    }
    for(int i=2;i<=K;i<<=1)
        for(int l=0;l<i>>1;l++)
        {
            register int W=w[v][K/i*l],*p=x+l+(i>>1),*q=x+l,t;
            for(register int j=0;j<K;j+=i)
            {
                p[j]=(q[j]-(t=(ll)p[j]*W%MOD)<0)?(q[j]-t+MOD):(q[j]-t);
                q[j]=(q[j]>=MOD-t)?(q[j]-MOD+t):(q[j]+t);
            }
        }
    if(!v) return;
    for(int i=0;i<K;i++) x[i]=x[i]*rv%MOD;
}
ll ff[SZ]; int A[SZ],B[SZ],C[SZ];
inline void calc(int*h,int*o,int d,int k)
{
    int off=k-d-1; ff[0]=1;
    for(int j=1;j<=d+d+3;++j)
    {
        int s=(j+off)%MOD; if(s<0) s+=MOD;
        ff[j]=ff[j-1]*(ll)s%MOD;
    }
    fftinit(d+d+d+5);
    memset(A,0,sizeof(A[0])*K);
    memset(B,0,sizeof(B[0])*K);
    for(int i=0;i<=d;++i)
    {
        A[i]=h[i]*(ll)rfac[i]%MOD*rfac[d-i]%MOD;
        if((d-i)&1) A[i]=(MOD-A[i])%MOD;
    }
    for(int i=0;i<=d+d;++i)
        B[i]=qp(i-d+k,MOD-2);
    if(K<=(1<<16))
    {
        fft(A,0); fft(B,0);
        for(int i=0;i<K;++i) C[i]=(ll)A[i]*B[i]%MOD;
        fft(C,1);
    }
    else //这里可能是错的，注意
    {
        fftinit(K>>1);
        fft(A,0); fft(A+K,0);
        fft(B,0); fft(B+K,0);
        for(int i=0;i<K;++i)
            C[i+K]=(A[i]*(ll)B[i+K]+(ll)B[i]*A[i+K])%MOD;
        for(int i=0;i<K;++i)
            C[i]=A[i]*(ll)B[i]%MOD;
        fft(C,1); fft(C+K,1);
    }
    for(int i=0;i<=d;++i)
    {
        //i+k-d...i+k
        o[i]=C[i+d]*ff[i+k-off]%MOD
        *qp(ff[i+k-d-off-1],MOD-2)%MOD;
        (o[i]<0)?(o[i]+=MOD):0;
    }
}
int V; ll rV;
int aa[SZ],bb[SZ];
inline void work(int x,vector<int>&v)
{
    if(x==0) {v.pb(1); return;}
    if(x&1)
    {
        work(x-1,v);
        for(int i=0;i<v.size();++i)
            v[i]=(ll)v[i]*(i*V+x)%MOD;
        ll p=1;
        for(int i=1;i<=x;++i)
            p=p*(V*x+i)%MOD;
        v.pb(p); return;
    }
    int d=x>>1; work(d,v);
    for(int i=0;i<=d;++i) aa[i]=v[i];
    calc(aa,aa+d+1,d,d+1);
    calc(aa,bb,d+d,d*rV%MOD);
    v.resize(x+1);
    for(int i=0;i<=x;++i)
        v[i]=aa[i]*(ll)bb[i]%MOD;
}
inline ll gfac_(int x)
{
    V=sqrt(x); rV=qp(V,MOD-2);
    vector<int> tmp; work(V,tmp); ll ans=1;
    for(int i=0;i<V;++i) ans=ans*tmp[i]%MOD;
    for(int i=V*V+1;i<=x;++i) ans=ans*i%MOD;
    return ans;
}
inline ll gfac(int x)
{
    if(x>=MOD) return 0;
    if(x>MOD-x-1)
    {
        int s=qp(gfac(MOD-x-1),MOD-2);
        if(x%2);else s=-s; return s;
    }
    return gfac_(x);
}
int main()
{
	int n; scanf("%d%d",&n,&MOD);
   	fac[0]=1; for(int i=1;i<SZ;++i) fac[i]=fac[i-1]*i%MOD;
   	rfac[SZ-1]=qp(fac[SZ-1],MOD-2);
   	for(int i=SZ-1;i>=1;--i) rfac[i-1]=rfac[i]*i%MOD;
   	G=org_root(); int ans=gfac(n)%MOD;
	//题目要求，n为奇数，输出n!/2
	if (n & 1) ans = 1ll * ans * ((MOD + 1) / 2) % MOD;
   	ans%=MOD; if(ans<0) ans+=MOD;
   	printf("%d\n",int(ans)); 
   	return 0; 
}
