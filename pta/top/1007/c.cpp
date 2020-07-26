#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int mod = 1000000007;
int n, low, high;
long long dpB[maxn][maxn]={}, dpR[maxn][maxn]={}, ans = 0;
int main(){
    scanf("%d", &n);
    dpB[1][1] = 1, dpB[2][1] = 2;
    dpR[1][1] = 1;
    for(int i = 3; i <= n; ++ i){
        low = log2(i+1)/2, high = log2(i+1)*2;
        for(int j = low; j <= high; ++ j){
            for(int k = 1; k < i-1; ++ k){
                dpB[i][j] = (dpB[i][j] + (((dpB[k][j-1]+dpR[k][j])*(dpB[i-1-k][j-1]+dpR[i-1-k][j]))%mod))% mod;
                dpR[i][j] = (dpR[i][j] + (dpB[k][j-1] * dpB[i-1-k][j-1]) % mod) % mod;
            }
        }
    }
	cout << dpR[0][1] << endl;
    for(int i = 0; i < 30; ++ i)
        ans = (ans + dpB[n][i]) % mod;
    printf("%lld", ans);
}
