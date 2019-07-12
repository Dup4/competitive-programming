#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 3010
const ll p = 998244353;
int n;
ll f[N][N], D;
void add(ll &x, ll y) {
	x += y;
	if (x >= p) x -= p;
}

int main() {
	memset(f, 0, sizeof f);
	f[1][1] = 1;
	for (int i = 2; i <= 3000; ++i) {
		for (int j = 0; j <= i; ++j) {
			//新加入的夫妻一起坐最后一排，他们两个可以互换位置
			if (j) add(f[i][j], 2ll * f[i - 1][j - 1] % p);
			//新加入的夫妻其中一个跟前面的配对夫妻互换,从j + 1转移过来
			add(f[i][j], 8ll * (j + 1) % p * f[i - 1][j + 1] % p);
			//新加入的夫妻其中一个跟前面的不配对的人互换，从j转移过来
			add(f[i][j], 8ll * (i - 1 - j) % p * f[i - 1][j] % p);	
			//新加入的夫妻两个都坐到前面去
			//和已经配对的交换，从j - 1转移过来
			if (j) add(f[i][j], 2ll * (j - 1) % p * f[i - 1][j - 1] % p);
			//和不配对的交换，交换过去还是配对的
			add(f[i][j], 2ll * ()
			

			
		}
	}
	while (scanf("%d%d", &n, &D) != EOF) {
	
	}
	return 0;
}
