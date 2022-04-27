#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef double ld;
int n, m, id[10010];
ld a[1010][10010], vv[10010];
const ld eps = 1e-10;
int dcmp(ld x) {
    if (x < -eps)
        return -1;
    if (x > eps)
        return 1;
    return 0;
}
void pivot(int r, int c)  //基变量r和非基变量c
{
    swap(id[r + n], id[c]);
    ld x = -a[r][c];
    a[r][c] = -1;
    for (int i = 0; i <= n; i++) a[r][i] /= x;
    for (int i = 0; i <= m; i++) {
        if (dcmp(a[i][c]) && i != r)
            ;
        else
            continue;
        x = a[i][c];
        a[i][c] = 0;
        for (int j = 0; j <= n; j++) a[i][j] += x * a[r][j];
    }
}
ld solve() {
    for (int i = 1; i <= n; i++) id[i] = i;
    while (1)  // init
    {
        int x = 0, y = 0;
        for (int i = 1; i <= m; i++) {
            if (dcmp(a[i][0]) < 0 && (!x || (rand() & 1)))
                x = i;
        }
        if (!x)
            break;
        for (int i = 1; i <= n; i++) {
            if (dcmp(a[x][i]) > 0 && (!y || (rand() & 1))) {
                y = i;
                break;
            }
        }
        if (!y) {
            puts("Infeasible");
            return 0;
        }
        pivot(x, y);
    }
    while (1)  // simplex
    {
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            if (dcmp(a[0][i]) > 0 && (!x || (rand() & 1)))
                x = i;
        }
        if (!x)
            break;
        double w, t;
        bool f = 1;
        for (int i = 1; i <= m; i++) {
            if (dcmp(a[i][x]) < 0 && ((t = -a[i][0] / a[i][x]), f || t < w))
                w = t, y = i, f = 0;
        }
        if (!y) {
            puts("Unbounded");
            return 0;
        }
        pivot(y, x);
    }
    return a[0][0];
    // printf("%.9lf\n",a[0][0]);
    // if(!t) return;
    // for(int i=1;i<=n;i++) vv[i]=0;
    // for(int i=n+1;i<=n+m;i++) vv[id[i]]=a[i-n][0];
    // for(int i=1;i<=n;i++) printf("%.9lf ",vv[i]);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lf", &a[i][0]);
    for (int i = 1, l, r, d; i <= m; ++i) {
        scanf("%d%d%d", &l, &r, &d);
        a[0][i] = d;
        for (int j = l; j <= r; ++j) {
            a[j][i] = -1;
        }
    }
    printf("%.0f\n", solve());
}

// int main() {
//	while (scanf("%d%d", &n, &m) != EOF) {
//		vector <vector<int> > A(n + 2, vector <int>(m + 2, 0));
//		for (int i = 1; i <= n; ++i) scanf("%d", a + i), A[i][0] = a[i];
//		for (int i = 1, l, r, d; i <= m; ++i) {
//			scanf("%d%d%d", &l, &r, &d);
//			A[0][i] = d;
//			for (int j = l; j <= r; ++j)
//				A[j][i] = 1;
//		}
//		LP lp(A, n, m);
//		printf("%d\n", lp.solve());
//	}
//	return 0;
// }
