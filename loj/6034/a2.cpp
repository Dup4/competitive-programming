#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
typedef double db;
const db INF = 2e18;
const db eps = 1e-10;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}
const int N = 1e5 + 10;

bool __slp__x__;
template <typename T>
struct HULL {
    T INF = 2e18;
    struct node {
        T slp, x, y;
        node(T _slp = 0, T _x = 0, T _y = 0) : slp(_slp), x(_x), y(_y) {}
        bool operator<(const node &other) const {
            return __slp__x__ ? slp > other.slp : x < other.x;
        }
        T operator-(const node &other) const {
            return (y - other.y) / (x - other.x);
        }
    };
    set<node> Q;
    void init() {
        Q.clear();
    }
    void ins(T x, T y) {
        __slp__x__ = 0;
        node t(0, x, y);
        typename set<node>::iterator it = Q.lower_bound(node(0, x, 0));
        if (it != Q.end()) {
            if ((it->x == x && it->y >= y) || (it->x != x && it->slp <= *it - t))
                return;
            if (it->x == x)
                Q.erase(it);
        }
        it = Q.insert(t).first;
        typename set<node>::iterator it3 = it;
        it3--;
        while (it != Q.begin()) {
            typename set<node>::iterator it2 = it3;
            if (it2 != Q.begin() && t - *it2 >= *it2 - *--it3)
                Q.erase(it2);
            else
                break;
        }
        it3 = it;
        it3++;
        while (it3 != Q.end()) {
            typename set<node>::iterator it2 = it3;
            if (++it3 != Q.end() && *it2 - *it3 >= *it2 - t)
                Q.erase(it2);
            else
                break;
        }
        if (it == Q.begin())
            const_cast<T &>(it->slp) = INF;
        else {
            typename set<node>::iterator it2 = it;
            it2--;
            const_cast<T &>(it->slp) = t - *it2;
        }
        typename set<node>::iterator it2 = it;
        it2++;
        if (it2 != Q.end())
            const_cast<T &>(it2->slp) = t - *it2;
    }
    T get(T a, T b) {
        // max(ax + by)
        if (Q.empty())
            return -INF;
        __slp__x__ = 1;
        typename set<node>::iterator it = Q.lower_bound(node(-a / b, 0, 0));
        if (it != Q.begin())
            it--;
        return it->x * a + it->y * b;
    }
};

struct SEG {
    HULL<db> t[N << 2];
    void build(int id, int l, int r) {
        t[id].init();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, db k, db b) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].ins(k, b);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, k, b);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, k, b);
    }
    db query(int id, int l, int r, int x) {
        db res = t[id].get(x, 1);
        if (l == r)
            return res;
        int mid = (l + r) >> 1;
        if (x <= mid)
            res = max(res, query(id << 1, l, mid, x));
        else
            res = max(res, query(id << 1 | 1, mid + 1, r, x));
        return res;
    }
} seg;

int main() {
    int m, q;
    while (scanf("%d%d", &m, &q) != EOF) {
        int n = 100000;
        seg.build(1, 1, n);
        int op, x[2], y[2];
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < 2; ++j) {
                scanf("%d%d", x + j, y + j);
            }
            if (x[0] > x[1]) {
                swap(x[0], x[1]);
                swap(y[0], y[1]);
            }
            db K, B;
            if (x[0] == x[1]) {
                K = 0;
                B = max(y[0], y[1]);
            } else {
                K = 1.0 * (y[0] - y[1]) / (x[0] - x[1]);
                B = y[0] - K * x[0];
            }
            seg.update(1, 1, n, max(1, x[0]), min(n, x[1]), K, B);
        }
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%d", &op);
            if (op == 0) {
                for (int j = 0; j < 2; ++j) {
                    scanf("%d%d", x + j, y + j);
                }
                if (x[0] > x[1]) {
                    swap(x[0], x[1]);
                    swap(y[0], y[1]);
                }
                db K, B;
                if (x[0] == x[1]) {
                    K = 0;
                    B = max(y[0], y[1]);
                } else {
                    K = 1.0 * (y[0] - y[1]) / (x[0] - x[1]);
                    B = y[0] - K * x[0];
                }
                seg.update(1, 1, n, max(1, x[0]), min(n, x[1]), K, B);
            } else {
                scanf("%d", x);
                db res = seg.query(1, 1, n, x[0]);
                if (sgn(res + INF) == 0)
                    res = 0;
                printf("%.6f\n", res);
            }
        }
    }
    return 0;
}
