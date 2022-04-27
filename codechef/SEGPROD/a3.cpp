#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, p, q, b[N];

template <typename CatTreeItem, CatTreeItem base>
struct CatTree {
    int lev, sz;
    vector<CatTreeItem> v;
    vector<vector<CatTreeItem>> t;
    //确立两数运算规则
    CatTreeItem op(const CatTreeItem &a, const CatTreeItem &b) {
        return 1ll * a * b % p;
    }
    int log2Up(int n) {
        return 31 - __builtin_clz(n);
    }
    void build(int id, int l, int r) {
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        t[id][mid] = v[mid];
        for (int i = mid - 1; i >= l; --i) t[id][i] = op(t[id][i + 1], v[i]);
        if (mid < r) {
            t[id][mid + 1] = v[mid + 1];
            for (int i = mid + 2; i <= r; ++i) t[id][i] = op(t[id][i - 1], v[i]);
        }
        build(id + 1, l, mid);
        build(id + 1, mid + 1, r);
    }
    //下标从0开始
    CatTree(const vector<CatTreeItem> &a) {
        int n = a.size();
        lev = __builtin_clz(n);
        sz = 1 << (31 - lev);
        if (n != sz) {
            sz <<= 1;
            --lev;
        }
        v = vector<CatTreeItem>(sz, base);
        t = vector<vector<CatTreeItem>>(log2Up(n) + 1, vector<CatTreeItem>(sz, base));
        for (int i = 0; i < n; ++i) v[i] = a[i];
        build(0, 0, sz - 1);
    }
    CatTreeItem query(int l, int r) {
        if (l == r)
            return v[l];
        int id = __builtin_clz(l ^ r) - lev - 1;
        return op(t[id][l], t[id][r]);
    }
};

int log2Up(int n) {
    return 32 - __builtin_clz(n);
}

int main() {
    cout << log2Up(8) << endl;
    return 0;
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d%d", &n, &p, &q);
        vector<int> a(n);
        for (int i = 0, x; i < n; ++i) {
            scanf("%d", &x);
            a[i] = x;
        }
        CatTree<int, 1> catTree(a);
        m = (q / 64) + 2;
        for (int i = 0; i < m; ++i) scanf("%d", b + i);
        int lst = 0;
        for (int i = 0, l = 0, r = 0; i < q; ++i) {
            if (i % 64 == 0) {
                l = (b[i / 64] + lst) % n;
                r = (b[i / 64 + 1] + lst) % n;
            } else {
                l = (l + lst) % n;
                r = (r + lst) % n;
            }
            if (l > r)
                swap(l, r);
            lst = (catTree.query(l, r) + 1) % p;
        }
        printf("%d\n", lst);
    }
    return 0;
}
