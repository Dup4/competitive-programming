#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct FHQ {
#define ls t[x].son[0]
#define rs t[x].son[1]
    struct node {
        int son[2], key, rnd, sze;
    } t[N];
    int tot, rt;
    void init() {
        tot = rt = 0;
    }
    void pushup(int x) {
        t[x].sze = t[ls].sze + t[rs].sze + 1;
    }
    int random() {
        static int seed = 703;
        return seed = int(seed * 48217ll % 2147483647);
    }
    int newnode(int key) {
        ++tot;
        t[tot].sze = 1;
        t[tot].key = key;
        t[tot].rnd = random();
        t[tot].son[0] = t[tot].son[1] = 0;
        return tot;
    }
    //默认x < y
    //假设第一棵树的权值小于等于第二棵树的权值，那么就比较它们的随机权值
    //如果rnd[l] < rnd[r]，那么保留第一棵树的左子树，另一棵树作为它的右子树
    //如果rnd[l] >= rnd[r]，那么保留第二棵树的右子树，另一棵树作为它的左子树
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
            //将所有权值小于等于key的保留在左边
            if (t[now].key <= key) {
                x = now;
                split(t[now].son[1], key, t[now].son[1], y);
                //权值大于key的去右边
            } else {
                y = now;
                split(t[now].son[0], key, x, t[now].son[0]);
            }
            pushup(now);
        }
        //最终得到的根为x的树，里面的权值是小于key的
        //得到的根为y的树，里面的权值是大于key的
    }
    //获得第k大的节点编号，根据二叉搜索树性质去找即可
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
    //查询key的排名，若有多个相同的数，输出最小的排名
    //按照key - 1将树分成x, y两棵，那么x树中最大的权值应该小于等于a - 1, 那么a的排名就是sze[x] + 1
    int getRank(int key) {
        int x, y;
        split(rt, key - 1, x, y);
        int res = t[x].sze + 1;
        rt = merge(x, y);
        return res;
    }
    //插入一个数key
    //先按权值key将树分成两段，x树中是权值小于等于key的，y树中是权值大于key的
    //那么新建一个节点z，它的权值为key，那么先将x, z合并起来，再将x和y合并起来
    void insert(int key) {
        int x, y;
        split(rt, key, x, y);
        rt = merge(merge(x, newnode(key)), y);
    }
    //删除一个数key，若有相同的数，只删除一个
    //先将整棵树以key为权值分裂成a, b两棵树，再将a树按照key - 1，分裂成c, d
    //那么这个时候权值为key的点一定是d的根，那么相当于要删去d的根
    //那么将d的两个子树merge起来当作新根，就相当于删去了根
    void del(int key) {
        int x, y, z;
        split(rt, key, x, z);
        split(x, key - 1, x, y);
        y = merge(t[y].son[0], t[y].son[1]);
        rt = merge(merge(x, y), z);
    }
    //求key的前驱，即小于key并且最大的数
    //按照key - 1的划分成x, y，那么小于key的数都在x中，直接输出x中最大的数即可　
    int getpre(int key) {
        int x, y;
        split(rt, key - 1, x, y);
        int res = t[getkth(x, t[x].sze)].key;
        rt = merge(x, y);
        return res;
    }
    //求key的后继，即大于key并且最小的数
    //按照key划分成x, y，那么大于key的数都在y中，直接输出y中最小的数即可
    int getnx(int key) {
        int x, y;
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
