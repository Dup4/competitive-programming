#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int n, q, a[N], res[N];

struct Hash {
    vector<int> a;
    int& operator[](int x) {
        return a[x - 1];
    }
    int size() {
        return a.size();
    }
    void init() {
        a.clear();
    }
    void add(int x) {
        a.push_back(x);
    }
    void gao() {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }
    int get(int x) {
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }
} hs;

struct BIT {
    int a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, int v) {
        for (; x < N; x += x & -x) a[x] += v;
    }
    int query(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x) res += a[x];
        return res;
    }
    int query(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} bit;

namespace BinarySearchPlus {
struct qnode {
    //-1删除 0 询问 1添加
    int tp, id, l, r, k, x;
    qnode() {}
    qnode(int tp, int id, int l, int r, int k, int x) : tp(tp), id(id), l(l), r(r), k(k), x(x) {}
} qrr[N], qleft[N], qright[N];
int tot = 0;
void init() {
    tot = 0;
}
void addQuery(int id, int l, int r, int k) {
    qrr[++tot] = qnode(0, id, l, r, k, 0);
}
void addModify(int tp, int x, int v) {
    qrr[++tot] = qnode(tp, 0, 0, 0, x, v);
    hs.add(v);
}
//[l, r]操作域 [L, R]值域
void solve(int l, int r, int L, int R) {
    if (l > r)
        return;
    if (L == R) {
        for (int i = l; i <= r; ++i) {
            if (qrr[i].tp == 0) {
                res[qrr[i].id] = hs[L];
            }
        }
        return;
    }
    int MID = (L + R) >> 1;
    int cntl = 0, cntr = 0, cnt = l - 1;
    for (int i = l; i <= r; ++i) {
        if (qrr[i].tp) {  //修改操作
            if (qrr[i].x <= MID) {
                qleft[++cntl] = qrr[i];
                bit.update(qrr[i].k, qrr[i].tp);
            } else {
                qright[++cntr] = qrr[i];
            }
        } else {  //查询操作
            int tot = bit.query(qrr[i].l, qrr[i].r);
            if (tot >= qrr[i].k) {
                qleft[++cntl] = qrr[i];
            } else {
                qright[++cntr] = qrr[i];
                qright[cntr].k -= tot;
            }
        }
    }
    for (int i = l; i <= r; ++i) {
        if (qrr[i].tp && qrr[i].x <= MID) {
            bit.update(qrr[i].k, -qrr[i].tp);
        }
    }
    for (int i = 1; i <= cntl; ++i) {
        qrr[++cnt] = qleft[i];
    }
    for (int i = 1; i <= cntr; ++i) {
        qrr[++cnt] = qright[i];
    }
    solve(l, l + cntl - 1, L, MID);
    solve(l + cntl, r, MID + 1, R);
}
void gao() {
    memset(res, -1, sizeof res);
    hs.gao();
    for (int i = 1; i <= tot; ++i)
        if (qrr[i].tp) {
            qrr[i].x = hs.get(qrr[i].x);
        }
    solve(1, tot, 1, hs.size());
}
}  // namespace BinarySearchPlus

int main() {
    while (scanf("%d", &n) != EOF) {
        hs.init();
        BinarySearchPlus::init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            BinarySearchPlus::addModify(1, i, a[i]);
        }
        scanf("%d", &q);
        for (int i = 1, op, x, y, k; i <= q; ++i) {
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                BinarySearchPlus::addModify(-1, x, a[x]);
                BinarySearchPlus::addModify(1, x, a[x] = y);
            } else if (op == 2) {
                scanf("%d", &k);
                BinarySearchPlus::addQuery(i, x, y, k);
            }
        }
        BinarySearchPlus::gao();
        for (int i = 1; i <= q; ++i) {
            if (res[i] != -1) {
                printf("%d\n", res[i]);
            }
        }
    }
    return 0;
}
