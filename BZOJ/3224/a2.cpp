#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, rnd, sze;
    } t[N];
    int tot, rt, x, y, z;
    inline void init() {
        tot = rt = 0;
    }
    inline void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
    }
    inline int random() {
        static int seed = rand();
        return seed = int(seed * 48217ll % 2147483647);
    }
    inline int newnode(int key) {
        ++tot;
        t[tot].sze = 1;
        t[tot].key = key;
        t[tot].rnd = random();
        t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    //默认x < y
    int merge(int x, int y) {
        if (!x || !y)
            return x + y;
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
    //以权值key分离now成x, y
    void split(int now, int key, int &x, int &y) {
        if (!now)
            x = y = 0;
        else {
            //将所有小于key的权值的节点分到一棵树中
            if (t[now].key <= key) {
                x = now;
                split(t[now].son[1], key, t[now].son[1], y);
            } else {
                y = now;
                split(t[now].son[0], key, x, t[now].son[0]);
            }
            pushup(now);
        }
    }
    //获得第k大的节点
    int getkth(int x, int k) {
        while (1) {
            if (k <= t[ls].sze) {
                x = ls;
            } else {
                if (k == t[ls].sze + 1)
                    return x;
                else {
                    k -= t[ls].sze + 1;
                    x = rs;
                }
            }
        }
    }
    //插入一个数key
    inline void insert(int key) {
        split(rt, key, x, y);
        rt = merge(merge(x, newnode(key)), y);
    }
    //删除一个数key，若有相同的数，只删除一个
    inline void del(int key) {
        split(rt, key, x, z);
        split(x, key - 1, x, y);
        y = merge(t[y].son[0], t[y].son[1]);
        rt = merge(merge(x, y), z);
    }
    //查询key的排名，若有多个相同的数，输出最小的排名
    inline int getRank(int key) {
        split(rt, key - 1, x, y);
        int res = t[x].sze + 1;
        rt = merge(x, y);
        return res;
    }
    //求key的前驱，即小于key并且最大的数
    inline int getpre(int key) {
        split(rt, key - 1, x, y);
        int res = t[getkth(x, t[x].sze)].key;
        rt = merge(x, y);
        return res;
    }
    //求key的后继，即大于key并且最小的数
    inline int getnx(int key) {
        split(rt, key, x, y);
        int res = t[getkth(y, 1)].key;
        rt = merge(x, y);
        return res;
    }
} fhq;

int main() {
    fhq.init();
    int q;
    scanf("%d", &q);
    int op, x;
    while (q--) {
        scanf("%d%d", &op, &x);
        switch (op) {
            case 1:
                fhq.insert(x);
                break;
            case 2:
                fhq.del(x);
                break;
            case 3:
                printf("%d\n", fhq.getRank(x));
                break;
            case 4:
                printf("%d\n", fhq.t[fhq.getkth(fhq.rt, x)].key);
                break;
            case 5:
                printf("%d\n", fhq.getpre(x));
                break;
            case 6:
                printf("%d\n", fhq.getnx(x));
                break;
        }
    }
    return 0;
}
