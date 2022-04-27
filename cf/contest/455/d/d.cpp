#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

const double alpha = 0.75;
struct Node {
    Node *ch[2];
    int size, key, nodeCount;
    bool exist;
    map<int, int> mp;
    bool isBad() {
        return ch[0]->nodeCount > alpha * nodeCount + 5 || ch[1]->nodeCount > alpha * nodeCount + 5;
    }
    void push_up() {
        size = exist + ch[0]->size + ch[1]->size;
        nodeCount = 1 + ch[0]->nodeCount + ch[1]->nodeCount;
        mp.clear();
        if (exist)
            mp[key]++;
        for (map<int, int>::iterator it = ch[0]->mp.begin(); it != ch[0]->mp.end(); it++)
            mp[(*it).first] += (*it).second;
        for (map<int, int>::iterator it = ch[1]->mp.begin(); it != ch[1]->mp.end(); it++)
            mp[(*it).first] += (*it).second;
    }
};

struct ScapeGoatTree {
    Node pool[N];
    Node *tail, *root, *null;
    Node *bc[N];  //内存回收
    int bc_top;
    void init() {
        tail = pool;
        null = tail++;
        null->ch[0] = null->ch[1] = null;
        null->size = null->key = null->nodeCount = 0;
        null->mp.clear();
        root = null;
        bc_top = 0;
    }
    inline Node *newNode(int key) {
        Node *p;
        if (bc_top)
            p = bc[--bc_top];
        else
            p = tail++;
        p->ch[0] = p->ch[1] = null;
        p->size = p->nodeCount = 1;
        p->key = key;
        p->exist = true;
        p->mp.clear();
        p->mp[key] = 1;
        return p;
    }
    Node *buildTree(int *a, int l, int r) {
        if (l >= r)
            return null;
        int mid = (l + r) >> 1;
        Node *p = newNode(a[mid]);
        p->ch[0] = buildTree(a, l, mid);
        p->ch[1] = buildTree(a, mid + 1, r);
        p->push_up();
        return p;
    }
    inline void Travel(Node *p, vector<Node *> &v) {
        if (p == null)
            return;
        Travel(p->ch[0], v);
        if (p->exist)
            v.push_back(p);
        else
            bc[bc_top++] = p;
        Travel(p->ch[1], v);
    }
    inline Node *divide(vector<Node *> &v, int l, int r) {
        if (l >= r)
            return null;
        int mid = (l + r) / 2;
        Node *p = v[mid];
        p->ch[0] = divide(v, l, mid);
        p->ch[1] = divide(v, mid + 1, r);
        p->push_up();
        return p;
    }
    //重构，注意p要引用
    inline void rebuild(Node *&p) {
        vector<Node *> v;
        Travel(p, v);
        p = divide(v, 0, v.size());
    }
    //删除第id个元素，返回第id个元素的值
    inline int erase(Node *p, int id) {
        if (p->exist && id == p->ch[0]->size + 1) {
            p->exist = 0;
            p->mp[p->key]--;
            p->size--;
            return p->key;
        }
        p->size--;
        int res;
        if (p->ch[0]->size >= id)
            res = erase(p->ch[0], id);
        else
            res = erase(p->ch[1], id - p->ch[0]->size - p->exist);
        p->mp[res]--;
        return res;
    }
    //删除一定的点以后重构
    void check_erase() {
        if (root->size < 0.5 * root->nodeCount)
            rebuild(root);
    }
    Node **insert(Node *&p, int id, int val) {
        if (p == null) {
            p = newNode(val);
            return &null;
        } else {
            p->size++;
            p->nodeCount++;
            p->mp[val]++;
            Node **res;
            if (id <= p->ch[0]->size + p->exist)
                res = insert(p->ch[0], id, val);
            else
                res = insert(p->ch[1], id - p->ch[0]->size - p->exist, val);
            if (p->isBad())
                res = &p;
            return res;
        }
    }
    //在第id个位置插入数val
    void insert(int id, int val) {
        Node **p = insert(root, id, val);
        if (*p != null)
            rebuild(*p);
    }
    //查询[l,r]之间值为val的数的个数
    int query(Node *p, int l, int r, int val) {
        if (p == null)
            return 0;
        if (l <= 1 && p->size <= r)
            return p->mp.count(val) ? p->mp[val] : 0;
        else {
            int ans = 0;
            if (l <= p->ch[0]->size)
                ans += query(p->ch[0], l, r, val);
            if (r > p->ch[0]->size + p->exist)
                ans += query(p->ch[1], l - p->ch[0]->size - p->exist, r - p->ch[0]->size - p->exist, val);
            if (p->exist && p->key == val && l <= p->ch[0]->size + 1 && r >= p->ch[0]->size + 1)
                ans++;
            return ans;
        }
    }
} tree;

int a[N];
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        tree.init();
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        tree.root = tree.buildTree(a, 0, n);
        int m;
        int op, l, r, k;
        scanf("%d", &m);
        int ans = 0;
        while (m--) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &l, &r);
                l = ((l + ans - 1) % n) + 1;
                r = ((r + ans - 1) % n) + 1;
                if (l > r)
                    swap(l, r);
                int v = tree.erase(tree.root, r);
                // tree.check_erase(); //有时候可以加上删除重构
                tree.insert(l, v);
            } else {
                scanf("%d%d%d", &l, &r, &k);
                l = ((l + ans - 1) % n) + 1;
                r = ((r + ans - 1) % n) + 1;
                k = ((k + ans - 1) % n) + 1;
                if (l > r)
                    swap(l, r);
                ans = tree.query(tree.root, l, r, k);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
