#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, m;
char s[N], t[N];
struct SEG {
    struct node {
        int Max, Min, lazy;
        node() {
            Max = Min = lazy = 0;
        }
        void up(int x) {
            Max += x;
            Min += x;
            lazy += x;
        }
        node operator+(const node &other) const {
            node res = node();
            res.Max = max(Max, other.Max);
            res.Min = min(Min, other.Min);
            return res;
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
        int &lazy = t[id].lazy;
        if (lazy) {
            t[id << 1].up(lazy);
            t[id << 1 | 1].up(lazy);
            lazy = 0;
        }
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
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
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].Max;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

void add(int pos, int f) {
    if (t[pos] == '(') {
        seg.update(1, 1, m, pos, m, 1 * f);
    } else if (t[pos] == ')') {
        seg.update(1, 1, m, pos, m, -1 * f);
    }
}

int main() {
    m = 1e6;
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        int pos = 1;
        seg.build(1, 1, m);
        memset(t, 0, sizeof t);
        for (int i = 1; s[i]; ++i) {
            if (s[i] == 'L') {
                pos = max(1, pos - 1);
            } else if (s[i] == 'R') {
                ++pos;
            } else {
                add(pos, -1);
                t[pos] = s[i];
                add(pos, 1);
                //	cout << i << endl;
                //	for (int j = 1; j <= 10; ++j) {
                //		cout << t[j];
                //	}
                //	cout << endl;
            }
            int res = -1;
            if (seg.t[1].Min != 0 || seg.query(1, 1, m, m) != 0) {
                res = -1;
            } else {
                res = seg.t[1].Max;
            }
            printf("%d%c", res, " \n"[i == n]);
        }
    }
    return 0;
}
