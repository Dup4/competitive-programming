#include <bits/stdc++.h>
using namespace std;
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
#define fi first
#define se second
const int N = 1e5 + 10;
int n, q, a[N];

struct ScapegoatTree {
#define ls(o) t[o].ls
#define rs(o) t[o].rs
    const double alpha = 0.76;
    struct node {
        int ls, rs, v, sz, valid;
        bool del;
        unordered_map<int, int> mp;
        node() {}
        void init(int x) {
            ls = rs = 0;
            v = x;
            sz = valid = 1;
            del = 0;
            mp.clear();
            ++mp[x];
        }
    } t[N * 10];
    int tot = 0, rt = 0;
    void init() {
        rt = 0;
        tot = 0;
    }
    int newnode(int x = 0) {
        ++tot;
        t[tot].init(x);
        return tot;
    }
    bool bad(int o) {
        return (double)t[ls(o)].sz > alpha * t[o].sz || (double)t[rs(o)].sz > alpha * t[o].sz;
    }
    void pushup(int o) {
        t[o].sz = t[ls(o)].sz + t[rs(o)].sz + !t[o].del;
        t[o].valid = t[ls(o)].valid + t[rs(o)].valid + !t[o].del;
        t[o].mp.clear();
        if (!t[o].del)
            ++t[o].mp[t[o].v];
        for (auto &it : t[ls(o)].mp) t[o].mp[it.fi] += it.se;
        for (auto &it : t[rs(o)].mp) t[o].mp[it.fi] += it.se;
    }
    void dfs(int o, vector<int> &v) {
        if (!o)
            return;
        dfs(ls(o), v);
        if (!t[o].del)
            v.push_back(o);
        dfs(rs(o), v);
        return;
    }
    int build(vector<int> &v, int l, int r) {
        if (l >= r)
            return 0;
        int mid = (l + r) >> 1;
        int o = v[mid];
        ls(o) = build(v, l, mid);
        rs(o) = build(v, mid + 1, r);
        pushup(o);
        return o;
    }
    void reBuild(int &o) {
        vector<int> v;
        dfs(o, v);
        o = build(v, 0, (int)v.size());
    }
    //在第id个位置插入x
    void insert(int &o, int id, int x) {
        if (!o) {
            o = newnode(x);
            return;
        }
        t[o].sz++;
        t[o].valid++;
        t[o].mp[x]++;
        if (id <= t[ls(o)].valid + !t[o].del)
            insert(ls(o), id, x);
        else
            insert(rs(o), id - t[ls(o)].valid - !t[o].del, x);
        if (bad(o))
            reBuild(o);
        return;
    }
    //删除第id个数
    int del(int o, int id) {
        if (!t[o].del && id == t[ls(o)].valid + 1) {
            t[o].del = 1;
            t[o].mp[t[o].v]--;
            t[o].valid--;
            return t[o].v;
        }
        t[o].valid--;
        int x = 0;
        if (t[ls(o)].valid >= id)
            x = del(ls(o), id);
        else
            x = del(rs(o), id - t[ls(o)].valid - !t[o].del);
        t[o].mp[x]--;
        return x;
    }
    int query(int o, int l, int r, int x) {
        if (!o)
            return 0;
        if (l <= 1 && t[o].valid <= r) {
            return t[o].mp.count(x) ? t[o].mp[x] : 0;
        } else {
            int ans = 0;
            if (l <= t[ls(o)].valid)
                ans += query(ls(o), l, r, x);
            if (r > t[ls(o)].valid + !t[o].del)
                ans += query(rs(o), l - t[ls(o)].valid - !t[o].del, r - t[ls(o)].valid - !t[o].del, x);
            if (!t[o].del && t[o].v == x && l <= t[ls(o)].valid + 1 && r >= t[ls(o)].valid + 1)
                ans++;
            return ans;
        }
    }
} scapegoatTree;

int decode(int x, int lst) {
    return ((x + lst - 1) % n + 1);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        scapegoatTree.init();
        for (int i = 1; i <= n; ++i) scapegoatTree.insert(scapegoatTree.rt, i, a[i]);
        scanf("%d", &q);
        int lst = 0;
        while (q--) {
            static int op, l, r, K;
            scanf("%d%d%d", &op, &l, &r);
            l = decode(l, lst);
            r = decode(r, lst);
            if (l > r)
                swap(l, r);
            if (op == 1) {
                int x = scapegoatTree.del(scapegoatTree.rt, r);
                scapegoatTree.insert(scapegoatTree.rt, l, x);
            } else {
                scanf("%d", &K);
                K = decode(K, lst);
                lst = scapegoatTree.query(scapegoatTree.rt, l, r, K);
                printf("%d\n", lst);
            }
        }
    }
    return 0;
}
