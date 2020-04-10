#include <bits/stdc++.h>
using namespace std;
const int N = 510, M = 6e4 + 10, INF = 0x3f3f3f3f;
int n, q, m, ans[M];

struct BIT {
    int a[N][N];
    void init() { memset(a, 0, sizeof a); }
    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= n; j += j & -j)
                a[i][j] += val;
    }
    int query(int x, int y) {
        int res = 0;
        for (int i = x; i; i -= i & -i)
            for (int j = y; j; j -= j & -j)
                res += a[i][j];
        return res;
    }
    int query(int x[], int y[]) {
        int res = 0;
        res += query(x[0] - 1, y[0] - 1);
        res += query(x[1], y[1]);
        res -= query(x[0] - 1, y[1]);
        res -= query(x[1], y[0] - 1);
        return res; 
    }
}bit;

struct node {
    int x, y, v;
	void scan(int _x, int _y) { x = _x, y = _y; scanf("%d", &v); }
    bool operator < (const node &r) const { return v < r.v; }
}arr[N * N];

namespace BinarySearchPlus {
	struct qnode {
	    int x[2], y[2], k, id;
	    void scan(int id) {
	        this->id = id;
	        for (int i = 0; i < 2; ++i)
	            scanf("%d%d", x + i, y + i);
	        scanf("%d", &k);
	    } 
	}que[M], ql[M], qr[M];
	//[l, r]操作域 [L, R]值域
	void solve(int l, int r, int L, int R) {
	    if (l > r) return;
	    if (L == R) {
	        for (int i = l; i <= r; ++i)
	            ans[que[i].id] = arr[L].v; 
	        return;  
	    }
	    int MID = (L + R) >> 1;
	    for (int i = L; i <= MID; ++i) bit.update(arr[i].x, arr[i].y, 1);
	    int posl = 0, posr = 0;  
	    for (int i = l; i <= r; ++i) {
	        int sze = bit.query(que[i].x, que[i].y);
	        if (sze < que[i].k)  {
	            que[i].k -= sze;
	            qr[++posr] = que[i];    
	        }
	        else
	            ql[++posl] = que[i];
	    }
	    for (int i = 1; i <= posl; ++i) que[l + i - 1] = ql[i];
	    for (int i = 1; i <= posr; ++i) que[l + posl + i - 1] = qr[i];
	    for (int i = L; i <= MID; ++i) bit.update(arr[i].x, arr[i].y, -1);
	    solve(l, l + posl - 1, L, MID);
	    solve(l + posl, r, MID + 1, R); 
	}
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        m = 0; bit.init();
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) arr[++m].scan(i, j);
        sort(arr + 1, arr + 1 + m);
        for (int i = 1; i <= q; ++i) BinarySearchPlus::que[i].scan(i);
		BinarySearchPlus::solve(1, q, 1, m); 
        for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
