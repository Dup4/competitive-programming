#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define MAX 100100
#define lson (now << 1)
#define rson (now << 1 | 1)
inline int read() {
    int x = 0;
    bool t = false;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-')
        t = true, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
    return t ? -x : x;
}
int N = 100000;
struct Node {
    bool fl;
    int id;
    double k, b;
    void upd(int _id, double _k, double _b) {
        id = _id, k = _k;
        b = _b;
    }
} t[MAX << 2];
double K[MAX], B[MAX];
void Modify(int now, int l, int r, int id, double k, double b) {
    if (!t[now].fl) {
        t[now].fl = true;
        t[now].upd(id, k, b);
        return;
    }
    int mid = (l + r) >> 1;
    double l1 = l * t[now].k + t[now].b, r1 = r * t[now].k + t[now].b;
    double l2 = l * k + b, r2 = r * k + b;
    if (l1 >= l2 && r1 >= r2)
        return;
    if (l2 > l1 && r2 > r1) {
        t[now].upd(id, k, b);
        return;
    }
    double x = (t[now].b - b) / (k - t[now].k);
    if (x <= mid) {
        if (l1 > l2)
            Modify(lson, l, mid, t[now].id, t[now].k, t[now].b), t[now].upd(id, k, b);
        else
            Modify(lson, l, mid, id, k, b);
    } else {
        if (l1 > l2)
            Modify(rson, mid + 1, r, id, k, b);
        else
            Modify(rson, mid + 1, r, t[now].id, t[now].k, t[now].b), t[now].upd(id, k, b);
    }
}
void Modify(int now, int l, int r, int L, int R, int id, double k, double b) {
    if (L <= l && r <= R) {
        Modify(now, l, r, id, k, b);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        Modify(lson, l, mid, L, R, id, k, b);
    if (R > mid)
        Modify(rson, mid + 1, r, L, R, id, k, b);
}
void Cmax(int &a, int b, int x) {
    double ya = K[a] * x + B[a];
    double yb = K[b] * x + B[b];
    if (ya < yb || (fabs(ya - yb) < 1e-7 && a > b))
        a = b;
}
int Query(int now, int l, int r, int x) {
    if (l == r)
        return t[now].id;
    int mid = (l + r) >> 1, ret = t[now].id;
    if (x <= mid)
        Cmax(ret, Query(lson, l, mid, x), x);
    else
        Cmax(ret, Query(rson, mid + 1, r, x), x);
    return ret;
}
int Q, ans, tot;
int main() {
    Q = read();
    while (Q--) {
        int opt = read();
        if (!opt) {
            int x = ((read() + ans - 1) % 39989 + 1);
            ans = Query(1, 1, N, x);
            printf("%d\n", ans);
        } else {
            int x0 = (read() + ans - 1) % 39989 + 1, y0 = (read() + ans - 1) % 1000000000 + 1;
            int x1 = (read() + ans - 1) % 39989 + 1, y1 = (read() + ans - 1) % 1000000000 + 1;
            if (x0 > x1)
                swap(x0, x1), swap(y0, y1);
            cout << x0 << " " << x1 << endl;
            ++tot;
            K[tot] = 1.0 * (y0 - y1) / (x0 - x1);
            B[tot] = y0 - K[tot] * x0;
            Modify(1, 1, N, x0, x1, tot, K[tot], B[tot]);
        }
    }
    return 0;
}
