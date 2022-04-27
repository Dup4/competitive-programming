#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define rint register int
#define For(i, a, b) for (rint i = a; i <= b; ++i)
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 1e6 + 17;
int n, m, rt, cnt;
int a[N], id[N], fa[N], c[N][2];
int sum[N], sz[N], v[N], mx[N], lx[N], rx[N];
bool tag[N], rev[N];
// tag表示是否有统一修改的标记，rev表示是否有统一翻转的标记
// sum表示这个点的子树中的权值和，v表示这个点的权值
queue<int> q;
inline int read() {
    rint x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x * f;
}
inline void pushup(rint x) {
    rint l = c[x][0], r = c[x][1];
    sum[x] = sum[l] + sum[r] + v[x];
    sz[x] = sz[l] + sz[r] + 1;
    mx[x] = max(mx[l], max(mx[r], rx[l] + v[x] + lx[r]));
    lx[x] = max(lx[l], sum[l] + v[x] + lx[r]);
    rx[x] = max(rx[r], sum[r] + v[x] + rx[l]);
}
//上传记录标记
inline void pushdown(rint x) {
    rint l = c[x][0], r = c[x][1];
    if (tag[x]) {
        rev[x] = tag[x] = 0;  //我们有了一个统一修改的标记，再翻转就没有什么意义了
        if (l)
            tag[l] = 1, v[l] = v[x], sum[l] = v[x] * sz[l];
        if (r)
            tag[r] = 1, v[r] = v[x], sum[r] = v[x] * sz[r];
        if (v[x] >= 0) {
            if (l)
                lx[l] = rx[l] = mx[l] = sum[l];
            if (r)
                lx[r] = rx[r] = mx[r] = sum[r];
        } else {
            if (l)
                lx[l] = rx[l] = 0, mx[l] = v[x];
            if (r)
                lx[r] = rx[r] = 0, mx[r] = v[x];
        }
    }
    if (rev[x]) {
        rev[x] = 0;
        rev[l] ^= 1;
        rev[r] ^= 1;
        swap(lx[l], rx[l]);
        swap(lx[r], rx[r]);
        //注意，在翻转操作中，前后缀的最长上升子序列都反过来了，很容易错
        swap(c[l][0], c[l][1]);
        swap(c[r][0], c[r][1]);
    }
}
//下传标记
inline void rotate(rint x, rint &k) {
    rint y = fa[x], z = fa[y], l = (c[y][1] == x), r = l ^ 1;
    if (y == k)
        k = x;
    else
        c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y;
    fa[y] = x;
    fa[x] = z;
    c[y][l] = c[x][r];
    c[x][r] = y;
    pushup(y);
    pushup(x);
    //旋转操作，一定要上传记录标记
}
inline void splay(rint x, rint &k) {
    while (x != k) {
        int y = fa[x], z = fa[y];
        if (y != k) {
            if (c[z][0] == y ^ c[y][0] == x)
                rotate(x, k);
            else
                rotate(y, k);
        }
        rotate(x, k);
    }
}
//这是整个程序的核心之一，毕竟是伸展操作嘛
inline int find(rint x, rint rk) {
    pushdown(x);
    //因为所有的操作都需要find，所以我们只需在这里下传标记就行了
    rint l = c[x][0], r = c[x][1];
    if (sz[l] + 1 == rk)
        return x;
    if (sz[l] >= rk)
        return find(l, rk);
    else
        return find(r, rk - sz[l] - 1);
}
//这个find是我们整个程序的核心之二
//因为我们的区间翻转和插入及删除的操作的存在
//我们维护的区间的实际编号并不是连续的
//而，我们需要操作的区间又对应着平衡树的中序遍历中的那段区间
//所以这个find很重要
inline void recycle(rint x) {
    rint &l = c[x][0], &r = c[x][1];
    if (l)
        recycle(l);
    if (r)
        recycle(r);
    q.push(x);
    fa[x] = l = r = tag[x] = rev[x] = 0;
}
//这就是用时间换空间的回收冗余编号机制，很好理解
inline int split(rint k, rint tot) {
    rint x = find(rt, k), y = find(rt, k + tot + 1);
    splay(x, rt);
    splay(y, c[x][1]);
    return c[y][0];
}
//这个split操作是整个程序的核心之三
//我们通过这个split操作，找到[k+1,k+tot]，并把k,和k+tot+1移到根和右儿子的位置
//然后我们返回了这个右儿子的左儿子，这就是我们需要操作的区间
inline void query(rint k, rint tot) {
    rint x = split(k, tot);
    printf("%d\n", sum[x]);
}
inline void modify(rint k, rint tot, rint val) {
    rint x = split(k, tot), y = fa[x];
    v[x] = val;
    tag[x] = 1;
    sum[x] = sz[x] * val;
    if (val >= 0)
        lx[x] = rx[x] = mx[x] = sum[x];
    else
        lx[x] = rx[x] = 0, mx[x] = val;
    pushup(y);
    pushup(fa[y]);
    //每一步的修改操作，由于父子关系发生改变
    //及记录标记发生改变，我们需要及时上传记录标记
}
inline void rever(rint k, rint tot) {
    rint x = split(k, tot), y = fa[x];
    if (!tag[x]) {
        rev[x] ^= 1;
        swap(c[x][0], c[x][1]);
        swap(lx[x], rx[x]);
        pushup(y);
        pushup(fa[y]);
    }
    //同上
}
inline void erase(rint k, rint tot) {
    rint x = split(k, tot), y = fa[x];
    recycle(x);
    c[y][0] = 0;
    pushup(y);
    pushup(fa[y]);
    //同上
}
inline void build(rint l, rint r, rint f) {
    rint mid = (l + r) >> 1, now = id[mid], pre = id[f];
    if (l == r) {
        mx[now] = sum[now] = a[l];
        tag[now] = rev[now] = 0;
        //这里这个tag和rev的清0是必要，因为这个编号可能是之前冗余了
        lx[now] = rx[now] = max(a[l], 0);
        sz[now] = 1;
    }
    if (l < mid)
        build(l, mid - 1, mid);
    if (mid < r)
        build(mid + 1, r, mid);
    v[now] = a[mid];
    fa[now] = pre;
    pushup(now);
    //上传记录标记
    c[pre][mid >= f] = now;
    //当mid>=f时，now是插入到又区间取了，所以c[pre][1]=now，当mid<f时同理
}
inline void insert(rint k, rint tot) {
    For(i, 1, tot) a[i] = read();
    For(i, 1, tot) if (!q.empty()) id[i] = q.front(), q.pop();
    else id[i] = ++cnt;           //利用队列中记录的冗余节点编号
    build(1, tot, 0);             //将读入的tot个树建成一个平衡树
    rint z = id[(1 + tot) >> 1];  //取中点为根
    rint x = find(rt, k + 1), y = find(rt, k + 2);
    //首先，依据中序遍历，找到我们需要操作的区间的实际编号
    splay(x, rt);
    splay(y, c[x][1]);
    //把k+1(注意我们已经右移了一个单位）和(k+1)+1移到根和右儿子
    fa[z] = y;
    c[y][0] = z;
    //直接把需要插入的这个平衡树挂到右儿子的左儿子上去就好了
    pushup(y);
    pushup(x);
    //上传记录标记
}
//对于具体在哪里上传标记和下传标记
//可以这么记，只要用了split就要重新上传标记
//只有find中需要下传标记
//但其实，你多传几次是没有关系的，但是少传了就不行了
int main() {
    n = read(), m = read();
    mx[0] = a[1] = a[n + 2] = -inf;
    For(i, 1, n) a[i + 1] = read();
    For(i, 1, n + 2) id[i] = i;  //虚拟了两个节点1和n+2，然后把需要操作区间整体右移一个单位
    build(1, n + 2, 0);          //建树
    rt = (n + 3) >> 1;
    cnt = n + 2;  //取最中间的为根
    rint k, tot, val;
    char ch[10];
    while (m--) {
        scanf("%s", ch);
        if (ch[0] != 'M' || ch[2] != 'X')
            k = read(), tot = read();
        if (ch[0] == 'I')
            insert(k, tot);
        if (ch[0] == 'D')
            erase(k, tot);
        if (ch[0] == 'M') {
            if (ch[2] == 'X')
                printf("%d\n", mx[rt]);
            else
                val = read(), modify(k, tot, val);
        }
        if (ch[0] == 'R')
            rever(k, tot);
        if (ch[0] == 'G')
            query(k, tot);
    }
    return 0;
}
