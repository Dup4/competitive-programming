#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, sze, rnd;
    } t[N * 50];
    int rt[N], tot;
    void init() {
        tot = rt[0] = 0;
    }
    int random() {
        static int seed = 703;
        return seed = int(seed * 48271ll % 2147483647);
    }
    void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
    }
    int newnode(int key) {
        ++tot;
        t[tot].key = key;
        t[tot].sze = 1;
        t[tot].rnd = random();
        t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    int Copy(int x) {
        int y = ++tot;
        t[y] = t[x];
        return y;
    }
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
        if (t[x].rnd < t[y].rnd) {
            //复制节点
            x = Copy(x);
            t[x].son[1] = merge(t[x].son[1], y);
            pushup(x);
            return x;
        } else {
            y = Copy(y);
            t[y].son[0] = merge(x, t[y].son[0]);
            pushup(y);
            return y;
        }
    }
    void split(int now, int key, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            if (t[now].key <= key) {
                //复制节点
                x = Copy(now);
                split(t[x].son[1], key, t[x].son[1], y);
                pushup(x);
            } else {
                y = Copy(now);
                split(t[y].son[0], key, x, t[y].son[0]);
                pushup(y);
            }
        }
    }
    void del(int &rt, int key) {
        int x, y, z;
        split(rt, key, x, z);
        split(x, key - 1, x, y);
        y = merge(t[y].son[0], t[y].son[1]);
        rt = merge(merge(x, y), z);
    }
    void insert(int &rt, int key) {
        int x, y;
        split(rt, key, x, y);
        rt = merge(merge(x, newnode(key)), y);
    }
    int getkth(int x, int k) {
        while (1) {
            if (k <= t[ls].sze)
                x = ls;
            else {
                if (k == t[ls].sze + 1)
                    return x;
                else {
                    k -= t[ls].sze + 1;
                    x = rs;
                }
            }
        }
    }
    int getRank(int &rt, int key) {
        int x, y;
        split(rt, key - 1, x, y);
        int res = t[x].sze + 1;
        rt = merge(x, y);
        return res;
    }
    int getPre(int &rt, int key) {
        int x, y, res;
        split(rt, key - 1, x, y);
        if (!x)
            return -2147483647;
        res = t[getkth(x, t[x].sze)].key;
        rt = merge(x, y);
        return res;
    }
    int getNx(int &rt, int key) {
        int x, y, res;
        split(rt, key, x, y);
        if (!y)
            return 2147483647;
        res = t[getkth(y, 1)].key;
        rt = merge(x, y);
        return res;
    }
} fhq;

int main() {
    int q;
    scanf("%d", &q);
    fhq.init();
    int op, x, ver;
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d%d", &ver, &op, &x);
        fhq.rt[i] = fhq.rt[ver];
        int &rt = fhq.rt[i];
        switch (op) {
            case 1:
                fhq.insert(rt, x);
                break;
            case 2:
                fhq.del(rt, x);
                break;
            case 3:
                printf("%d\n", fhq.getRank(rt, x));
                break;
            case 4:
                printf("%d\n", fhq.t[fhq.getkth(rt, x)].key);
                break;
            case 5:
                printf("%d\n", fhq.getPre(rt, x));
                break;
            case 6:
                printf("%d\n", fhq.getNx(rt, x));
                break;
        }
    }
    return 0;
}
