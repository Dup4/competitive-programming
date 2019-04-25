#include <bits/stdc++.h>
using namespace std;

#define N 2010
#define ll long long
int n;
const ll p = (ll)1e9 + 7;
ll f[N][N][3]; 
bool used[N][N];
//0表示该点连出去的所有边都没有被选中
//1表示该点连向某个儿子的边被选中
//2表示该点连向其父亲的边被选中

//左儿子代表左括号，右儿子代表右括号 
void DFS(int l, int r) { 
    if (l > n || r > n || used[l][r]) {
		return;  
	}	
	DFS(l + 1, r);
	//有左右儿子
	if (l > r) {
		DFS(l, r + 1);
		int P = max(f[l + 1][r][0], f[l + 1][r][1]);
		int Q = max(f[l][r + 1][0], f[l][r + 1][1]);
		f[l][r][0] = (P + Q) % p;
		f[l][r][1] = (max(f[l + 1][r][2] + Q, f[l][r + 1][2] + P)) % p;
		f[l][r][2] = (P + Q + 1) % p;
	} else if (l == r) { //只有左儿子
		f[l][r][0] = max(f[l + 1][r][0], f[l + 1][r][1]); 
		f[l][r][1] = f[l + 1][r][2];
		f[l][r][2] = (max(f[l + 1][r][0], f[l + 1][r][1]) + 1) % p;  
	}
	used[l][r] = 1;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(f, 0, sizeof f);
		memset(used, 0, sizeof used);
		DFS(0, 0);
		printf("%lld\n", max(f[0][0][0], f[0][0][1]));      
	}
	return 0;
}
