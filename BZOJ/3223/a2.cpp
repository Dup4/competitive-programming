#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, q;
struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, rnd, sze, rev;
    } t[N];
    int tot, rt;
    inline void init() {
        tot = rt = 0;
    }
    inline void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
        if (x && t[x].rev) {
            t[x].rev ^= 1;
            swap(t[x].son[0], t[x].son[1]);
            t[ls].rev ^= 1;
            t[rs].rev ^= 1;
        }
    }
    inline int random() {
        static int seed = 703;
        return seed = int(seed * 482147ll % 2147483647);
    }
    inline int newnode(int key) {
        ++tot;
        t[tot].sze = 1;
        t[tot].key = key;
        t[tot].rnd = random();
        t[tot].rev = t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    int build(int l, int r) {
        if (l > r)
            return 0;
        int mid = (l + r) >> 1, v = mid - 1;
        int x = newnode(v);
        ls = build(l, mid - 1);
        rs = build(mid + 1, r);
        pushup(x);
        return x;
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        pushup(x);
        pushup(y);
        if (t[x].rnd < t[y].rnd) {
            t[x].son[1] = merge(t[x].son[1], y);
            pushup(x);
            return x;
        } else {
            t[y].son[0] = merge(x, t[y].son[0]);
            pushup(y);
            return y;
        }
    }
    //根据sze分
    inline void split(int now, int k, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            pushup(now);
            if (k <= t[t[now].son[0]].sze) {
                y = now;
                split(t[now].son[0], k, x, t[now].son[0]);
            } else {
                x = now;
                split(t[now].son[1], k - t[t[now].son[0]].sze - 1, t[now].son[1], y);
            }
            pushup(now);
        }
    }
    inline void rev(int l, int r) {
        int a, b, c, d;
        split(rt, r + 1, a, b);
        split(a, l, c, d);
        t[d].rev ^= 1;
        rt = merge(merge(c, d), b);
    }
    inline void print(int x) {
        if (!x)
            return;
        pushup(x);
        print(ls);
        if (t[x].key >= 1 && t[x].key <= n)
            printf("%d ", t[x].key);
        print(rs);
    }
} fhq;

int main() {
    fhq.init();
    scanf("%d%d", &n, &q);
    fhq.rt = fhq.build(1, n + 2);
    for (int i = 1, l, r; i <= q; ++i) {
        scanf("%d%d", &l, &r);
        fhq.rev(l, r);
    }
    fhq.print(fhq.rt);
    return 0;
}
