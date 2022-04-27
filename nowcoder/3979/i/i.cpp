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
const int N = 8e4 + 3, unit = 220;
int n, q, hs[N << 1], pos[N], posl[N], posr[N], singleMin[N], unitMin[N];

struct SEG {
    struct node {
        int sum, lazy, ls, rs;
        node() {}
        void init() {
            sum = 0;
            lazy = -1;
            ls = rs = 0;
        }
        void up(int x, int l, int r) {
            sum = x * (r - l + 1);
            lazy = x;
        }
    } t[N * 400];
    int rt[500], cnt;
    void init() {
        memset(rt, 0, sizeof rt);
        cnt = 0;
    }
    int newnode() {
        ++cnt;
        t[cnt].init();
        return cnt;
    }
    void down(int id, int l, int r) {
        int &lazy = t[id].lazy;
        if (lazy != -1) {
            int mid = (l + r) >> 1;
            if (t[id].ls == 0)
                t[id].ls = newnode();
            if (t[id].rs == 0)
                t[id].rs = newnode();
            t[t[id].ls].up(lazy, l, mid);
            t[t[id].rs].up(lazy, mid + 1, r);
            lazy = -1;
        }
    }
    void update(int &id, int l, int r, int ql, int qr, int v) {
        if (!id)
            id = newnode();
        if (l >= ql && r <= qr) {
            t[id].up(v, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        down(id, l, r);
        if (ql <= mid)
            update(t[id].ls, l, mid, ql, qr, v);
        if (qr > mid)
            update(t[id].rs, mid + 1, r, ql, qr, v);
        t[id].sum = t[t[id].ls].sum + t[t[id].rs].sum;
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (!id)
            return 0;
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        down(id, l, r);
        int res = 0;
        if (ql <= mid)
            res += query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[id].rs, mid + 1, r, ql, qr);
        return res;
    }
    void update1(int rt, int pos, int v) {
        int pre = query(rt, 1, *hs, pos, pos);
        update(rt, 1, *hs, pos, pos, pre + v);
    }
} seg;

struct OP {
    int tp, l, r, x;
    void input() {
        scanf("%d%d%d%d", &tp, &l, &r, &x);
        if (tp == 1) {
            x = min(x, n);
            hs[++*hs] = x;
        }
    }
} op[N];

void forceUpdate(int l, int r, int x) {
    for (int i = l; i <= r; ++i) {
        int pre = min(singleMin[i], unitMin[pos[i]]);
        if (x < pre) {
            seg.update1(seg.rt[pos[i]], x, 1);
            seg.update1(seg.rt[pos[i]], pre, -1);
            singleMin[i] = x;
        }
    }
}

int forceQuery(int l, int r, int x) {
    int res = 0;
    for (int i = l; i <= r; ++i) {
        int now = min(singleMin[i], unitMin[pos[i]]);
        if (now <= x)
            ++res;
    }
    return res;
}

void update(int l, int r, int x) {
    if (pos[l] == pos[r])
        forceUpdate(l, r, x);
    else {
        forceUpdate(l, posr[pos[l]], x);
        for (int i = pos[l] + 1; i < pos[r]; ++i) {
            int t = seg.query(seg.rt[i], 1, *hs, x, *hs);
            seg.update(seg.rt[i], 1, *hs, x, *hs, 0);
            seg.update(seg.rt[i], 1, *hs, x, x, t);
            unitMin[i] = min(unitMin[i], x);
        }
        forceUpdate(posl[pos[r]], r, x);
    }
}

int query(int l, int r, int x) {
    if (pos[l] == pos[r])
        return forceQuery(l, r, x);
    else {
        int res = forceQuery(l, posr[pos[l]], x) + forceQuery(posl[pos[r]], r, x);
        for (int i = pos[l] + 1; i < pos[r]; ++i) {
            res += seg.query(seg.rt[i], 1, *hs, 1, x);
        }
        return res;
    }
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        *hs = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", singleMin + i), hs[++*hs] = singleMin[i];
        for (int i = 1; i <= q; ++i) op[i].input();
        sort(hs + 1, hs + 1 + *hs);
        *hs = unique(hs + 1, hs + 1 + *hs) - hs - 1;
        for (int i = 1; i <= n; ++i) singleMin[i] = lower_bound(hs + 1, hs + 1 + *hs, singleMin[i]) - hs;
        for (int i = 1; i <= q; ++i) {
            if (op[i].tp == 1) {
                op[i].x = lower_bound(hs + 1, hs + 1 + *hs, op[i].x) - hs;
            }
        }
        for (int i = 1; i <= n; ++i) {
            pos[i] = (i - 1) / unit + 1;
            if (i == 1 || pos[i] != pos[i - 1])
                posl[pos[i]] = i;
            posr[pos[i]] = i;
        }
        seg.init();
        for (int i = 1; i <= pos[n]; ++i) {
            seg.rt[i] = seg.newnode();
            unitMin[i] = n + 1;
        }
        for (int i = 1; i <= n; ++i) {
            seg.update1(seg.rt[pos[i]], singleMin[i], 1);
        }
        for (int i = 1; i <= q; ++i) {
            if (op[i].tp == 1) {
                update(op[i].l, op[i].r, op[i].x);
            } else {
                int l = 1, r = *hs, res = -1;
                while (r - l >= 0) {
                    int mid = (l + r) >> 1;
                    if (query(op[i].l, op[i].r, mid) >= op[i].x) {
                        res = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                printf("%d\n", hs[res]);
            }
        }
    }
    return 0;
}
