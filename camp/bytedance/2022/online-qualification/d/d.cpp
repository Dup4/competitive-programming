//#include<iostream>
//#include<algorithm>
//#include<set>
//#include<vector>
//#include<list>
//#include<queue>
//#include<cmath>
//#include<cstring>
//#include<sstream>
//#include<cstdio>
//#include<ctime>
//#include<map>
//#include<bitset>
//#include<stack>
//#include<string>
// using namespace std;
//#define ll long long
//#define pii pair<int,int>
////constexpr int N = 2e5 + 10;
// const int maxn = 4e5 + 10;
// const int mod=998244353;
// ll rd(){
//    ll x;
//    scanf("%lld",&x);
//    return x;
//}
// int n;
// char s[maxn][3];
// int cnt[4][3];
// ll fac[maxn]={1},inv[maxn]={1};
// ll C(int n,int m){
////    printf("%d %d\n",n,m);
//    if(n<0||m<0)return 0;
//    if(n==0||m==0)return 1;
//    return fac[n]*inv[m]%mod*inv[n-m]%mod;
//}
// ll qpow(ll a,ll b){
//    ll c=1;
//    while(b){
//        if(b&1)c=c*a%mod;
//        b>>=1;
//        a=a*a%mod;
//    }
//    return c;
//}
// int fit(int row,string s1){
//    if(s[row][1]!='?' && s1[0]!=s[row][1])return 0;
//    if(s[row][2]!='?' && s1[1]!=s[row][2])return 0;
//    return (s[row][1]=='?') + (s[row][2]=='?');
//}
// pii get(string s){
//    pii p(0,0);
//    for(int i=0;i<2;i++){
//        p.first+=s[i]=='W';
//        p.second+=s[i]=='B';
//    }
//    return p;
//}
// bool WB(){
//    if(cnt[1][2]+cnt[2][1])return 0;
//    return 1;
//}
// bool BW(){
//    if(cnt[1][1]+cnt[2][2])return 0;
//    return 1;
//}
// ll ans;
// void dfs(int row,pii p,ll k){
//    k%=mod;
//    ans%=mod;
//    if(p.first>n||p.second>n)return;
//    if(row>n){
//        return;
//    }
//    if(s[row][1]==s[row][2] && s[row][1]!='?'){
//        ans+=C(2*n-p.first-p.second,n-p.first)*k%mod;
//        return;
//    }
//
//}
////  W=1  B=0
// int main(){
//    n=rd();
//    for(int i=1;i<=2*n;i++){
//        fac[i]=fac[i-1]*i%mod;
//        inv[i]=qpow(fac[i],mod-2);
//    }
//    int w=0,b=0;
//    for(int i=1;i<=n;i++){
////        s[i][1]=s[i][2]='?';
//        scanf("%s",s[i]+1);
//        for(int j=1;j<=2;j++){
//            cnt[j][1]+=s[i][j]=='W';
//            cnt[j][2]+=s[i][j]=='B';
//            w+=s[i][j]=='W';
//            b+=s[i][j]=='B';
//        }
//    }
//    if(n==1){
//        printf("%d\n",WB()+BW());
//        return 0;
//    }
//    dfs(1,w,b,0,0,1);
//    printf("%lld\n",(ans +WB()+BW())%mod);
//}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define ll long long
#define pii pair<int, int>
// constexpr int N = 2e5 + 10;
const int maxn = 4e5 + 10;
const int mod = 998244353;
ll rd() {
    ll x;
    scanf("%lld", &x);
    return x;
}
int n;
char s[maxn][3];
int cnt[4][3];
ll fac[maxn] = {1}, inv[maxn] = {1};
set<string> se;
ll C(int n, int m) {
    //    printf("%d %d\n",n,m);
    if (n < 0 || m < 0)
        return 0;
    if (n == 0 || m == 0)
        return 1;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll qpow(ll a, ll b) {
    ll c = 1;
    while (b) {
        if (b & 1)
            c = c * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return c;
}
int fit(int row, string s1) {
    if (s[row][1] != '?' && s1[0] != s[row][1])
        return 0;
    if (s[row][2] != '?' && s1[1] != s[row][2])
        return 0;
    return (s[row][1] == '?') + (s[row][2] == '?');
}
bool WB() {
    if (cnt[1][2] + cnt[2][1])
        return 0;
    return 1;
}
bool BW() {
    if (cnt[1][1] + cnt[2][2])
        return 0;
    return 1;
}
ll ans;
void dfs(int row, int w, int b, ll k) {
    k %= mod;
    ans %= mod;
    if (w > n || b > n)
        return;
    if (row > n) {
        return;
    }
    if (s[row][1] == s[row][2] && s[row][1] != '?') {
        // WW or BB
        ans += C(2 * n - w - b, n - w) * k % mod;
        return;
    }
    if (fit(row, "WW")) {
        // ??  W?  ?W
        int w1 = w + fit(row, "WW");
        ans += k * C(2 * n - w1 - b, n - w1) % mod;
    }
    if (fit(row, "BB")) {
        // ??  B?  ?B
        int b1 = b + fit(row, "BB");
        ans += k * C(2 * n - w - b1, n - b1) % mod;
    }
    if (s[row][1] == '?' && s[row][2] == '?') {
        // ?? -> WB  BW
        dfs(row + 1, w + 1, b + 1, k * 2);
        return;
    }
    if (s[row][1] != '?' && s[row][2] != '?') {
        // WB  BW
        dfs(row + 1, w, b, k);
        return;
    }
    if (s[row][1] == 'W' || s[row][2] == 'W') {
        dfs(row + 1, w, b + 1, k);
        return;
    }
    if (s[row][1] == 'B' || s[row][2] == 'B') {
        dfs(row + 1, w + 1, b, k);
        return;
    }
}
//  W=1  B=0
int main() {
    n = rd();
    for (int i = 1; i <= 2 * n; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i], mod - 2);
    }
    int w = 0, b = 0;
    int k = 1;
    for (int i = 1; i <= n; i++) {
        //        s[i][1]=s[i][2]='?';
        scanf("%s", s[i] + 1);
        if (s[i][1] == s[i][2] && s[i][1] != '?') {
            k = i;
        }
        for (int j = 1; j <= 2; j++) {
            cnt[j][1] += s[i][j] == 'W';
            cnt[j][2] += s[i][j] == 'B';
            w += s[i][j] == 'W';
            b += s[i][j] == 'B';
        }
    }
    swap(s[k], s[1]);
    if (n == 1) {
        printf("%d\n", WB() + BW());
        return 0;
    }
    dfs(1, w, b, 1);
    printf("%lld\n", (ans + WB() + BW()) % mod);
}

/*
4
??
??
WW
BB

5
WB
??
WB
??
??
??

 */