#include <bits/stdc++.h>
using namespace std;
#define psi pair<string, int>
#define fi first
#define se second
#define N 300010
#define ALP 26

struct ACAM {
    struct node {
        int nx[ALP], fail;
        int cnt;
        node() {
            memset(nx, -1, sizeof nx);
            cnt = 0;
        }
    };
    vector<psi> vec;
    vector<node> t;
    int root, tot;
    //节点从1开始
    ACAM() {
        vec.clear();
        t.clear();
    }
    int newnode() {
        ++tot;
        t.resize(tot + 10);
        t[tot] = node();
        return tot;
    }
    void init() {
        vec.clear();
    }
    void clear() {
        t.clear();
        tot = 0;
        root = newnode();
    }
    void insert(string s, int x) {
        int len = s.size();
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (t[now].nx[s[i] - 'a'] == -1)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
        }
        //表示以该结点结尾的模式串数量
        t[now].cnt += x;
    }
    void add(string s, int x) {
        vec.push_back(psi(s, x));
    }
    void build() {
        clear();
        for (auto it : vec) insert(it.fi, it.se);
        queue<int> q;
        t[root].fail = root;
        //将第二层出现过的字母扔进队列，并将fail指向根
        //对于没出现过的字母，直接将该字母的下一个节点指向根
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == -1) {
                t[root].nx[i] = root;
            } else {
                t[t[root].nx[i]].fail = root;
                q.push(t[root].nx[i]);
            }
        }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            t[now].cnt += t[t[now].fail].cnt;
            for (int i = 0; i < ALP; ++i) {
                //如果当前节点没有子节点i + 'a'
                //则让这个子节点指向当前节点fail指针对应的子节点
                if (t[now].nx[i] == -1) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    //如果当前节点有子节点i + 'a'
                    //则让这个子节点的fail指针指向(((它父亲节点)的fail指针指向的那个节点)的对应的子节点)
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    q.push(t[now].nx[i]);
                }
            }
        }
    }
    int query(string s) {
        int now = root;
        int len = s.size();
        int res = 0;
        for (int i = 0; i < len; ++i) {
            now = t[now].nx[s[i] - 'a'];
            res += t[now].cnt;
        }
        return res;
    }
} ac[25];
int tot;

void insert(string s, int f) {
    ++tot;
    ac[tot].init();
    ac[tot].add(s, f);
    while (tot > 1 && ac[tot].vec.size() == ac[tot - 1].vec.size()) {
        for (auto it : ac[tot].vec) {
            ac[tot - 1].add(it.fi, it.se);
        }
        --tot;
    }
    ac[tot].build();
}

int query(string s) {
    int res = 0;
    for (int i = 1; i <= tot; ++i) res += ac[i].query(s);
    return res;
}

void out(int x) {
    cout << x << "\n";
    cout.flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q, op;
    string s;
    while (cin >> q) {
        tot = 0;
        while (q--) {
            cin >> op >> s;
            if (op == 1) {
                insert(s, 1);
            } else if (op == 2) {
                insert(s, -1);
            } else {
                out(query(s));
            }
        }
    }
    return 0;
}
