#include <cstdio>
using namespace std;
const int N = 310; 
int best, n, m;
int x[N], path[N];
int num[N];
int g[N][N];

//点的标号[0, n - 1]
bool dfs(int *adj, int total, int cnt) { // total: 与u相连的顶点数量, cnt表示当前团的大小
    int i, j, k;
    int t[N];
    if (total == 0) { // 当此团中最后一个点没有比起序号大的顶点相连时  
        if (best < cnt) {  // best为最大团中顶点的数量 
            //保存方案
			for (i = 0; i < cnt; i++) path[i] = x[i]; 
            best = cnt; return true; 
        }    
        return false;
    }    
    for (i = 0; i < total; i++) { // 枚举每一个与u相连的顶点adj[i] 
		// 剪枝1  若当前顶点数量cnt 加上还能够增加的最大数量仍小于best则 退出并返回false 
        if (cnt + (total - i) <= best) return false;  
		// 剪枝2 若当前顶点数量cnt 加上包含adj[i]的最大团顶点数仍小于best则 退出并返回false 
        if (cnt + num[adj[i]] <= best) return false;  
		//保存方案
        x[cnt] = adj[i];  
		// 扫描与u相连的顶点中与adj[u]相连的顶点并存储到数组t[]中, 数量为k 
        for (k = 0, j = i + 1; j < total; j++) 
            if (g[adj[i]][adj[j]])
                t[k++] = adj[j];
        if (dfs(t, k, cnt + 1)) return true;
    } 
	return false;
} 

int MaximumClique(){
    int i, j, k;
    int adj[N];
    if( n <= 0 ) return 0;
    best = 0;
    for (i = n - 1; i >= 0; i--) {
        //保存方案
		x[0] = i; 
        for(k = 0, j = i + 1; j < n; j++)    // 遍历[i + 1, n]间顶点，  
            if (g[i][j]) adj[k++] = j;
        dfs(adj, k, 1); // *adj, total, cnt
        num[i] = best;   // 得出顶点 i, 出发构成最大团 中顶点数量 
    }    
    return best;
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < n; ++j)
				g[i][j] = 0;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			--u, --v;
			g[u][v] = 1;
		}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				g[i][j] ^= 1;
		printf("%d\n", MaximumClique());
		//输出方案
		for (int i = 0; i < best; ++i)
			printf("%d%c", path[i] + 1, " \n"[i == best - 1]);
	}
	return 0;
}
