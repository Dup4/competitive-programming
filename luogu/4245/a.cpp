#include <bits/stdc++.h>
using namespace std;
#define maxn 400005
#define LL long long
 
int n,m, RealMod;
int P[3]={998244353,1004535809,469762049},G[3]={3,3,3},invG[3],wn[3][2][maxn];
 
inline int pow(int base,int k,int P)
{
	int ret=1;
	for(;k;k>>=1,base=1ll*base*base%P) if(k&1) ret=1ll*ret*base%P;
	return ret;
}
 
inline void Prework(int id)
{
	invG[id]=pow(G[id],P[id]-2,P[id]);
	for(int i=1;i<24;i++) wn[id][1][i]=pow(G[id],(P[id]-1)/(1<<i),P[id]),wn[id][0][i]=pow(invG[id],(P[id]-1)/(1<<i),P[id]);
}
 
inline void NTT(int *A,int n,int typ,int id)
{
	for(int i=0,j=0,k;i<n;i++)
	{
		if(i<j) swap(A[i],A[j]);
		for(k=n>>1;k;k>>=1) if((j^=k)>=k) break;
	}
 
	for(int i=1,j,k,len,w,x,y;1<<i<=n;i++)	
	{
		len=1<<(i-1);
		for(j=0,w=1;j<n;j+=1<<i,w=1)
			for(k=0;k<len;k++,w=1ll*w*wn[id][typ][i]%P[id])
			{
				x=A[j+k],y=1ll*A[j+k+len]*w%P[id];
				A[j+k]=(x+y)%P[id];
				A[j+k+len]=(x-y+P[id])%P[id];
			}
	}
	
	if(typ==0)
		for(int i=0,inv=pow(n,P[id]-2,P[id]);i<n;i++)
			A[i]=1ll*A[i]*inv%P[id];
}
 
void mul(int *ret,int *A,int lena,int *B,int lenb,int id)
{
	static int seq1[maxn],seq2[maxn];
	int n=1;for(;n<=lena+lenb;n<<=1);
	for(int i=0;i<n;i++) 
	{
		if(i<=lena) seq1[i]=A[i]; else seq1[i]=0;
		if(i<=lenb) seq2[i]=B[i]; else seq2[i]=0;
	}
	NTT(seq1,n,1,id);NTT(seq2,n,1,id);
	for(int i=0;i<n;i++) ret[i]=1ll*seq1[i]*seq2[i]%P[id];
	NTT(ret,n,0,id);
}
 
//O(1)快速乘
//LL mul(LL a,LL b,LL P)
//{
//	a=(a%P+P)%P,b=(b%P+P)%P;
//	return ((a*b-(LL)((long double)a/P*b+1e-6)*P)%P+P)%P;
//}

LL mul(LL a, LL b, LL mod) {
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;

}

/*
long long mul (long long a, long long b, long long mod) {
	a%=mod,b%=mod;
    if (b == 0)
        return 0;
    long long ans = mul (a, b>>1, mod);
    ans = ans*2%mod;
    if (b&1) ans += a, ans %= mod;
    return (ans+mod)%mod;
}*/
 
 
int a[maxn],b[maxn],c[3][maxn];
LL Mod=1ll*P[0]*P[1];
LL inv1=pow(P[0],P[1]-2,P[1]),inv2=pow(P[1],P[0]-2,P[0]),inv=pow(Mod%P[2],P[2]-2,P[2]);
inline void solve(int i)
{
	LL C=(mul(1ll*c[0][i]*P[1]%Mod,inv2,Mod)+mul(1ll*c[1][i]*P[0]%Mod,inv1,Mod))%Mod;
	LL K=1ll*((1ll*c[2][i]-(C%P[2]))%P[2])*(inv%P[2])%P[2];
	c[0][i]=(((K%RealMod+RealMod)*(Mod%RealMod)%RealMod+C)%RealMod);
}
 
int main()
{
	
	//freopen("1.in","r",stdin);
	
	//int t1=clock();
	
	scanf("%d%d%d",&n,&m, &RealMod);
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	for(int j=0;j<=m;j++) scanf("%d",&b[j]);
	for(int i=0;i<3;i++) Prework(i),mul(c[i],a,n,b,m,i); 
	for(int i=0;i<=n+m;i++) 
		solve(i); 
	for(int i=0;i<n+m;i++)
	{
		int tmp=(c[0][i]+RealMod)%RealMod;
		printf("%d ",tmp);
	}
	printf("%d ",(c[0][n+m]+RealMod)%RealMod);
	
	//printf("%d\n",clock()-t1);
}
