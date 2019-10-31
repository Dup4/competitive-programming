#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 110;
int n, m, g[N][N];         

//点的编号[1, n]
struct Floyd {
	//r[i][j] i到j的最短路径的第一步
	//dist[i][j] i到j的最短路径
	//out[] 记录最小环
	int r[N][N], out[N], dist[N][N];
	void init() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] = INF;
                r[i][j] = i;
            }
        }
	}
    void getpath(int i, int j, int k) {
		*out = 0;
		while (j != i) {
			out[++*out] = j;
			j = r[i][j];
		}
		out[++*out] = i;
		out[++*out] = k;
	}
	void gao() {
        memmove(dist, g, sizeof(dist));
        int Min = INF;             
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i < k; i++) { //  一个环中的最大结点为k(编号最大) 
                if (g[k][i] < INF) {
                    for (int j = i + 1; j < k; j++) {
                        if (dist[i][j] < INF && g[k][j] < INF && Min > dist[i][j] + g[k][i] + g[k][j]) {
                            Min = dist[i][j] + g[k][i] + g[k][j];
                            getpath(i, j, k);     //  记录最小环
                        }
                    }
                }
            }
            for (int i = 1; i <= n; i++) {
                if (dist[i][k] < INF) {
                    for (int j = 1; j < n; j++) {
                        if (dist[k][j] < INF && dist[i][j] > dist[i][k]+dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            r[i][j] = r[k][j];
                        }
                    }
                }
            }
        }
        if (Min < INF) {
            printf("%d\n", Min);
			//输出路径
		//	for (; *out >= 1; --*out) {
		//		printf("%d%c", out[*out], " \n"[*out == 1]);
		//	}
		} else {
			puts("It's impossible.");
        }
	}
}floyd;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
		floyd.init();
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            if (w < g[u][v]) {
                g[u][v] = g[v][u] = w;
            }
        }
		floyd.gao();
    }
    return 0;
}
