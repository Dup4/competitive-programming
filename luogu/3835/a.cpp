#include <bits/stdc++.h>
#define R register
#define W while
#define IN inline
#define gc getchar()
#define MX 500005
static bool fu;
template <class T>
IN void in(T &x) {
    fu = false;
    R char c = gc;
    x = 0;
    W(!isdigit(c)) {
        if (c == '-')
            fu = true;
        c = gc;
    }
    W(isdigit(c)) {
        x = (x << 1) + (x << 3), x += c - 48, c = gc;
    }
    if (fu)
        x = -x;
}
namespace fhqTreap {
struct Node {
    int son[2], val, siz, pri;
} tree[MX * 50];
int root[MX];
int cnt;
IN int randomm() {
    static int seed = 703;
    return seed = int(seed * 48271LL % 2147483647);
}
IN void pushup(const int &now) {
    tree[now].siz = tree[tree[now].son[0]].siz + tree[tree[now].son[1]].siz + 1;
}
IN int new_node(const int &giv) {
    tree[++cnt].val = giv;
    tree[cnt].siz = 1;
    tree[cnt].pri = randomm();
    return cnt;
}
int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (tree[x].pri > tree[y].pri) {
        int now = ++cnt;
        tree[now] = tree[x];
        tree[now].son[1] = merge(tree[now].son[1], y);
        pushup(now);
        return now;
    } else {
        int now = ++cnt;
        tree[now] = tree[y];
        tree[now].son[0] = merge(x, tree[now].son[0]);
        pushup(now);
        return now;
    }
}
void split(int now, int k, int &x, int &y) {
    if (!now) {
        x = y = 0;
        return;
    }
    if (tree[now].val <= k) {
        x = ++cnt;
        tree[x] = tree[now];
        split(tree[x].son[1], k, tree[x].son[1], y);
        pushup(x);
    } else {
        y = ++cnt;
        tree[y] = tree[now];
        split(tree[y].son[0], k, x, tree[y].son[0]);
        pushup(y);
    }
}
void Del(int &root, int tar) {
    int x = 0, y = 0, z = 0;
    split(root, tar, x, z);
    split(x, tar - 1, x, y);
    y = merge(tree[y].son[0], tree[y].son[1]);
    root = merge(merge(x, y), z);
}
void insert(int &root, int tar) {
    int x = 0, y = 0, z = 0;
    split(root, tar, x, y);
    root = merge(merge(x, new_node(tar)), y);
}
int get_val(int now, int tar) {
    if (tar == tree[tree[now].son[0]].siz + 1)
        return tree[now].val;
    else if (tar <= tree[tree[now].son[0]].siz)
        return get_val(tree[now].son[0], tar);
    else
        return get_val(tree[now].son[1], tar - tree[tree[now].son[0]].siz - 1);
}
IN int kth(int &root, int tar) {
    int x, y;
    split(root, tar - 1, x, y);
    int ans = tree[x].siz + 1;
    root = merge(x, y);
    return ans;
}
IN int pre(int &root, int tar) {
    int x, y, k, ans;
    split(root, tar - 1, x, y);
    if (!x)
        return -2147483647;
    k = tree[x].siz;
    ans = get_val(x, k);
    root = merge(x, y);
    return ans;
}
IN int suc(int &root, int tar) {
    int x, y, ans;
    split(root, tar, x, y);
    if (!y)
        return 2147483647;
    else
        ans = get_val(y, 1);
    root = merge(x, y);
    return ans;
}
}  // namespace fhqTreap
using namespace fhqTreap;
int main(void) {
    int q;
    R int base, com, t;
    in(q);
    for (R int i = 1; i <= q; ++i) {
        in(base), in(com), in(t);
        root[i] = root[base];
        switch (com) {
            case 1: {
                insert(root[i], t);
                break;
            }
            case 2: {
                Del(root[i], t);
                break;
            }
            case 3: {
                printf("%d\n", kth(root[i], t));
                break;
            }
            case 4: {
                printf("%d\n", get_val(root[i], t));
                break;
            }
            case 5: {
                printf("%d\n", pre(root[i], t));
                break;
            }
            case 6: {
                printf("%d\n", suc(root[i], t));
                break;
            }
        }
    }
}
