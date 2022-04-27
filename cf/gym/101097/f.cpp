#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 3e5 + 10;
int n, m, q, res[N];
ll tar[N];
struct tnode {
    int l, r;
    ll a;
    tnode() {}
    tnode(int l, int r, ll a) : l(l), r(r), a(a) {}
    void scan() {
        scanf("%d%d%lld", &l, &r, &a);
    }
} arr[N];
struct qnode {
    int id;
    ll v;
    qnode() {}
    qnode(int id, ll v) : id(id), v(v) {}
} que[N], ql[N], qr[N];
vector<vector<int>> vec;

struct BIT {
    ll a[N];
    void init() {
        memset(a, 0, sizeof a);
    }
    void update(int x, ll v) {
        for (; x < N; x += x & -x) {
            a[x] += v;
        }
    }
    ll query(int x) {
        ll res = 0;
        for (; x > 0; x -= x & -x) {
            res += a[x];
        }
        return res;
    }
    void update(int l, int r, ll v) {
        if (l > r) {
            update(l, v);
            update(m + 1, -v);
            update(1, v);
            update(r + 1, -v);
        } else {
            update(l, v);
            update(r + 1, -v);
        }
    }
} bit;

void gao(int L, int R, int l, int r) {
    if (L > R)
        return;
    //	cout << L << " " << R << " " << l << " " << r << endl;
    if (l == r) {
        //	cout << l << endl;
        for (int i = L; i <= R; ++i) {
            res[que[i].id] = l;
        }
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = l; i <= mid; ++i) {
        bit.update(arr[i].l, arr[i].r, arr[i].a);
    }
    int posl = 0, posr = 0;
    for (int i = L; i <= R; ++i) {
        ll tot = 0;
        for (auto it : vec[que[i].id]) {
            tot += bit.query(it);
            if (tot > que[i].v)
                break;
        }
        //	cout << que[i].id << " " << tot << endl;
        if (tot < que[i].v) {
            que[i].v -= tot;
            qr[++posr] = que[i];
        } else {
            ql[++posl] = que[i];
        }
    }
    for (int i = 1; i <= posl; ++i) que[L + i - 1] = ql[i];
    for (int i = 1; i <= posr; ++i) que[L + posl + i - 1] = qr[i];
    for (int i = l; i <= mid; ++i) bit.update(arr[i].l, arr[i].r, -arr[i].a);
    gao(L, L + posl - 1, l, mid);
    gao(L + posl, R, mid + 1, r);
}

void out(int x) {
    if (x == q + 1)
        puts("NIE");
    else {
        printf("%d\n", x);
    }
}

int main() {
    freopen("meteors.in", "r", stdin);
    freopen("meteors.out", "w", stdout);
    while (scanf("%d%d", &n, &m) != EOF) {
        vec.clear();
        vec.resize(n + 1);
        bit.init();
        for (int i = 1; i <= n; ++i) res[i] = q + 1;
        for (int i = 1, x; i <= m; ++i) {
            scanf("%d", &x);
            vec[x].push_back(i);
        }
        for (int i = 1; i <= n; ++i) scanf("%lld", tar + i);
        scanf("%d", &q);
        for (int i = 1; i <= q; ++i) {
            arr[i].scan();
        }
        arr[q + 1] = tnode(1, m, 2000000000ll);
        for (int i = 1; i <= n; ++i) {
            que[i] = qnode(i, tar[i]);
        }
        gao(1, n, 1, q + 1);
        for (int i = 1; i <= n; ++i) out(res[i]);
    }
    return 0;
}
