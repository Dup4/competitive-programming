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
const int N = 1e5 + 10;
int n, q, a[N];

struct SEG {
    struct node {
        int ls, rs, v;
        node() {}
        void init() {
            ls = rs = v = 0;
        }
    } t[N * 60];
    int tot;
    int newnode() {
        ++tot;
        t[tot].init();
        return tot;
    }
    void init() {
        tot = 0;
    }
    void pushup(int id) {
        t[id].v = t[t[id].ls].v + t[t[id].rs].v;
    }
    void update(int &id, int l, int r, int pos, int v) {
        if (!id)
            id = newnode();
        if (l == r) {
            t[id].v += v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[id].ls, l, mid, pos, v);
        else
            update(t[id].rs, mid + 1, r, pos, v);
        pushup(id);
    }
    void merge(int &x, int y, int l, int r) {
        if (!x || !y) {
            x |= y;
            return;
        }
        if (l == r) {
            t[x].v += t[y].v;
            return;
        }
        int mid = (l + r) >> 1;
        merge(t[x].ls, t[y].ls, l, mid);
        merge(t[x].rs, t[y].rs, mid + 1, r);
        pushup(x);
    }
    // k表示保存在y中的区间长度
    void split(int &x, int y, int k, int opt) {
        if (t[y].v == k)
            return;
        x = newnode();
        t[x].v = t[y].v - k;
        t[y].v = k;
        if (opt) {
            if (k <= t[t[y].rs].v) {
                split(t[x].rs, t[y].rs, k, opt);
                t[x].ls = t[y].ls;
                t[y].ls = 0;
            } else {
                split(t[x].ls, t[y].ls, k - t[t[y].rs].v, opt);
            }
        } else {
            if (k <= t[t[y].ls].v) {
                split(t[x].ls, t[y].ls, k, opt);
                t[x].rs = t[y].rs;
                t[y].rs = 0;
            } else {
                split(t[x].rs, t[y].rs, k - t[t[y].ls].v, opt);
            }
        }
    }
    //查找区间第k大
    int query(int id, int l, int r, int k, int opt) {
        if (l == r)
            return l;
        int mid = (l + r) >> 1;
        if (opt) {
            if (k <= t[t[id].rs].v)
                return query(t[id].rs, mid + 1, r, k, opt);
            else
                return query(t[id].ls, l, mid, k - t[t[id].rs].v, opt);
        } else {
            if (k <= t[t[id].ls].v)
                return query(t[id].ls, l, mid, k, opt);
            else
                return query(t[id].rs, mid + 1, r, k - t[t[id].ls].v, opt);
        }
    }
} seg;

struct ODT {
    // opt 0 升序 1 降序
    struct node {
        int l;
        mutable int r, segrt, opt;
        node() {}
        node(int l, int r = -1, int segrt = 0, int opt = 0) : l(l), r(r), segrt(segrt), opt(opt) {}
        bool operator<(const node &other) const {
            return l < other.l;
        }
    };
    using IT = set<node>::iterator;
    set<node> se;
    void init() {
        se.clear();
    }
    IT split(int pos) {
        IT it = se.lower_bound(node(pos));
        if (it != se.end() && it->l == pos)
            return it;
        --it;
        int l = it->l, r = it->r, opt = it->opt, segrt = it->segrt, newsegrt;
        seg.split(newsegrt, it->segrt, pos - it->l, opt);
        se.erase(it);
        se.insert(node(l, pos - 1, segrt, opt));
        return se.insert(node(pos, r, newsegrt, opt)).first;
    }
    void assign(int l, int r, int opt) {
        IT itr = split(r + 1), itl = split(l), it = itl;
        itl->opt = opt;
        itl->r = r;
        for (++it; it != itr; ++it) {
            seg.merge(itl->segrt, it->segrt, 1, n);
        }
        it = itl;
        ++it;
        se.erase(it, itr);
    }
    int query(int pos) {
        IT it = se.upper_bound(node(pos));
        --it;
        return seg.query(it->segrt, 1, n, pos - it->l + 1, it->opt);
    }
} odt;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        seg.init();
        odt.init();
        for (int i = 1; i <= n; ++i) {
            auto it = odt.se.insert(ODT::node(i, i, 0, 0)).first;
            seg.update(it->segrt, 1, n, a[i], 1);
        }
        for (int i = 1, op, l, r; i <= q; ++i) {
            scanf("%d%d%d", &op, &l, &r);
            odt.assign(l, r, op);
        }
        int x;
        scanf("%d", &x);
        printf("%d\n", odt.query(x));
    }
    return 0;
}
