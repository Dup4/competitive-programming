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
    }
    inline void pushdown(int x) {
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
        int mid = (l + r) >> 1, v = mid;
        int x = newnode(v);
        ls = build(l, mid - 1);
        rs = build(mid + 1, r);
        pushup(x);
        return x;
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd) {
            pushdown(x);
            t[x].son[1] = merge(t[x].son[1], y);
            pushup(x);
            return x;
        } else {
            pushdown(y);
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
            pushdown(now);
            //将所有排名小于等于key的保留在左边
            if (k <= t[t[now].son[0]].sze) {
                y = now;
                split(t[now].son[0], k, x, t[now].son[0]);
                //将排名大于key的保留在右边
            } else {
                x = now;
                split(t[now].son[1], k - t[t[now].son[0]].sze - 1, t[now].son[1], y);
            }
            pushup(now);
        }
    }
    //先将整棵树以l - 1，分成两棵树a, b
    //那么b树中的排名为[l, n]，再将b树按r - l + 1，分成两棵树c, d
    //那么c树中的排名为[l, r]，将c树打上标记，再合并回去即可
    inline void rev(int l, int r) {
        int a, b, c;
        split(rt, l - 1, a, b);
        split(b, r - l + 1, b, c);
        t[b].rev ^= 1;
        rt = merge(a, merge(b, c));
    }
    inline void print(int x) {
        if (!x)
            return;
        pushdown(x);
        print(ls);
        printf("%d ", t[x].key);
        print(rs);
    }
} fhq;

int main() {
    fhq.init();
    scanf("%d%d", &n, &q);
    fhq.rt = fhq.build(1, n);
    for (int i = 1, l, r; i <= q; ++i) {
        scanf("%d%d", &l, &r);
        fhq.rev(l, r);
    }
    fhq.print(fhq.rt);
    return 0;
}
