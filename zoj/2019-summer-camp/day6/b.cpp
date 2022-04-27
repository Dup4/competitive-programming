#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 0x3f3f3f3f
#define N 500010
int n, m;
ll H[N];
struct node {
    ll a, b;
    node() {}
    void scan() {
        scanf("%lld%lld", &a, &b);
        H[++m] = a;
    }
    bool operator<(const node &other) const {
        return a + b < other.a + other.b;
    }
} a[N];

struct SEG {
    struct node {
        int x;
        ll sum;
        node() {
            x = sum = 0;
        }
        node(int x, ll sum) : x(x), sum(sum) {}
        node operator+(const node &other) const {
            node res = node();
            res.x = x + other.x;
            res.sum = sum + other.sum;
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int pos, int x) {
        if (l == r) {
            t[id].x += x;
            t[id].sum += H[l] * x;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos, x);
        else
            update(id << 1 | 1, mid + 1, r, pos, x);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, ll k) {
        if (l == r) {
            return k / H[l] + (k % H[l] != 0);
        }
        int mid = (l + r) >> 1;
        if (t[id << 1 | 1].sum >= k) {
            return query(id << 1 | 1, mid + 1, r, k);
        } else {
            return t[id << 1 | 1].x + query(id << 1, l, mid, k - t[id << 1 | 1].sum);
        }
    }
} seg;

int getid(int x) {
    return lower_bound(H + 1, H + 1 + m, x) - H;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        m = 0;
        for (int i = 1; i <= n; ++i) a[i].scan();
        sort(a + 1, a + 1 + n);
        sort(H + 1, H + 1 + m);
        m = unique(H + 1, H + 1 + m) - H - 1;
        int res = INF;
        seg.build(1, 1, m);
        for (int i = 1; i <= n; ++i) {
            if (seg.t[1].sum < a[i].b) {
                seg.update(1, 1, m, getid(a[i].a), 1);
                continue;
            }
            int now = seg.query(1, 1, m, a[i].b);
            // cout << i << " " << now << endl;
            res = min(res, now + 1);
            seg.update(1, 1, m, getid(a[i].a), 1);
        }
        if (res == INF)
            res = -1;
        printf("%d\n", res);
    }
    return 0;
}
