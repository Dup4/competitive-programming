#include <bits/stdc++.h>
using namespace std;

#define N 510
#define INF 0x3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second

struct fastio{
    static const int s=1<<24;
    int p,l;
    fastio(){p=l=0;}
    inline char gc(){
        static char bf[s];
        if(p==l)p=0,l=fread(bf,1,s,stdin);
        return p==l?-1:bf[p++];
    }
    inline bool read(int&x){
        char c=gc();
        while((c<'0'||c>'9')&&~c)c=gc();
        if(c==-1)return 0;x=0;
        for(;c>='0'&&c<='9';c=gc())x=x*10+c-'0';
        return 1;
    }
}io;

int a[N][N];
int f[N][N][9][9], g[N][N][9][9];
int mm[N];
inline void init(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j][0][0] = a[i][j];
			g[i][j][0][0] = a[i][j];
		}
	}
	for (int ii = 0; ii <= mm[n]; ++ii) {
		for (int jj = 0; jj <= mm[m]; ++jj) {
			if (ii + jj) {
				for (int i = 1; i + (1 << ii) - 1 <= n; ++i) {
					for (int j = 1; j + (1 << jj) - 1 <= m; ++j) {
						if (ii) {
							f[i][j][ii][jj] = max(f[i][j][ii - 1][jj], f[i + (1 << (ii - 1))][j][ii - 1][jj]);
							g[i][j][ii][jj] = min(g[i][j][ii - 1][jj], g[i + (1 << (ii - 1))][j][ii - 1][jj]);
						} else {
							f[i][j][ii][jj] = max(f[i][j][ii][jj - 1], f[i][j + (1 << (jj - 1))][ii][jj - 1]);
							g[i][j][ii][jj] = min(g[i][j][ii][jj - 1], g[i][j + (1 << (jj - 1))][ii][jj - 1]);
						}
					}
				}
			}
		}
	}
} 

inline void Max(int &x, int y) {
	if (x < y) x = y;
}

inline void Min(int &x, int y) {
	if (x > y) x = y;
}

inline pii rmq(int x1, int y1, int x2, int y2) {
	int k1 = mm[x2 - x1 + 1];
	int k2 = mm[y2 - y1 + 1];
	x2 = x2 - (1 << k1) + 1;
	y2 = y2 - (1 << k2) + 1;
	pii res = pii(-INF, INF);
	Max(res.fi, f[x1][y1][k1][k2]);
	Max(res.fi, f[x1][y2][k1][k2]);
	Max(res.fi, f[x2][y1][k1][k2]);
	Max(res.fi, f[x2][y2][k1][k2]);
	Min(res.se, g[x1][y1][k1][k2]);
	Min(res.se, g[x1][y2][k1][k2]);
	Min(res.se, g[x2][y1][k1][k2]);
	Min(res.se, g[x2][y2][k1][k2]);
	return res;
}

int main() {
	mm[0] = -1;
	for (int i = 1; i < N; ++i) {
		mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
	}
	int n, m;
	int T; io.read(T);
	while (T--) {
		io.read(n); io.read(m);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				io.read(a[i][j]);
			}
		}
		init(n, n);
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				int pos = 1;
				for (int k = 1; k <= n; ++k) {
					while (pos <= k) {
						pii tmp = rmq(i, pos, j, k);
						if (tmp.fi - tmp.se > m) ++pos;
						else break;
					}
					if (pos <= k) res = max(res, (j - i + 1) * (k - pos + 1));
					if ((j - i + 1) * (n - pos + 1) <= res) break;
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
