#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const int N = 1e5 + 10;
int n;
struct E {
    int x, y, id;
    E() {
        x = y = id = 0;
    }
    E(int x, int y, int id) : x(x), y(y), id(id) {}
    bool operator<(const E &other) const {
        return y < other.y;
    }
};
mt19937 rnd(time(0));
ull H[N], HA[N], HB[N], S[N];

struct SEG {
    struct node {
        ull v, lazy;
        node() {
            v = lazy = 0;
        }
        void up(ull x) {
            v ^= x;
            lazy ^= x;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void down(int id) {
        ull &lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up(lazy);
            t[id << 1 | 1].up(lazy);
            lazy = 0;
        }
    }
    void update(int id, int l, int r, int ql, int qr, ull v) {
        if (ql > qr)
            return;
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    ull query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].v;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

void gao(vector<E> &e, ull *Ha) {
    sort(e.begin() + 1, e.end());
    seg.build(1, 1, n);
    S[0] = 0;
    for (int i = 1; i <= n; ++i) S[i] = S[i - 1] ^ H[e[i].id];
    for (int i = 1; i <= n; ++i) {
        int l = 1, r = i, res = i;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (e[mid].y >= e[i].x) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        Ha[e[i].id] = S[i] ^ S[res - 1];
        seg.update(1, 1, n, res, i - 1, H[e[i].id]);
    }
    for (int i = 1; i <= n; ++i) Ha[e[i].id] ^= seg.query(1, 1, n, i);
}

void putans() {
    for (int i = 1; i <= n; ++i) {
        if (HA[i] != HB[i]) {
            puts("NO");
            return;
        }
    }
    puts("YES");
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) H[i] = rnd(), HA[i] = 0, HB[i] = 0;
        vector<E> A(n + 1), B(n + 1);
        for (int i = 1, s[2], e[2]; i <= n; ++i) {
            cin >> s[0] >> e[0] >> s[1] >> e[1];
            A[i] = E(s[0], e[0], i);
            B[i] = E(s[1], e[1], i);
        }
        gao(A, HA);
        gao(B, HB);
        putans();
    }
    return 0;
}
