#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define pii pair<int, int>
#define MP make_pair
#define fir first
#define sec second
typedef long long ll;
const int N=1e7+5;
inline int read(){
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1; c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0'; c=getchar();}
    return x*f;
}
 
int n, m, k;
int notp[N], p[N], g[N]; pii lp[N];
void sieve(int n) {
    g[1] = 0; 
    for(int i=2; i<=n; i++) {
        if(!notp[i]) {
            p[++p[0]] = i;
            g[i] = 1;
            lp[i] = MP(i, 1);
        }
        for(int j=1; j<=p[0] && i*p[j]<=n; j++) {
            int t = i*p[j]; 
            notp[t] = 1;
            if(i%p[j] == 0) {
                lp[t] = MP(lp[i].fir * p[j], lp[i].sec + 1);
                int rem = i / lp[i].fir;
                if(rem == 1) g[t] = 1;
                else g[t] = lp[t].sec == lp[rem].sec ? -g[rem] : 0;
                break;
            }
            lp[t] = MP(p[j], 1);
            g[t] = lp[t].sec == lp[i].sec ? -g[i] : 0;
        }
    }
    for(int i=1; i<=n; i++) g[i] += g[i-1];
}
ll cal(int n, int m) {
    if(n>m) swap(n, m);
    ll ans=0; int r;
    for(int i=1; i<=n; i=r+1) {
        r = min(n/(n/i), m/(m/i));
        ans += (ll) (g[r] - g[i-1]) * (n/i) * (m/i);
    }
    return ans;
}
 
int main() {
    //freopen("in","r",stdin);
    sieve(N-1);
    int T=read();
    while(T--) {
        n=read(); m=read();
        printf("%lld\n", cal(n, m));
    }
}
