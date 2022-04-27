#include <bits/stdc++.h>
using namespace std;
#define N 1000010
char s[N];
int n;

struct ACAM {
    int nx[N][26], fail[N], cnt[N], vis[N];
    int root, L;
    int newnode() {
        for (int i = 0; i < 26; ++i) nx[L][i] = -1;
        cnt[L++] = 0;
        return L - 1;
    }
    void init() {
        L = 0;
        root = newnode();
    }
    void insert(char *s) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (nx[now][s[i] - 'a'] == -1)
                nx[now][s[i] - 'a'] = newnode();
            now = nx[now][s[i] - 'a'];
        }
        ++cnt[now];
    }
    void build() {
        queue<int> q;
        fail[root] = root;
        //将第二层出现过的字母扔进队列，并将fail指向根
        //对于没出现过的字母，直接将该字母的下一个节点指向根
        for (int i = 0; i < 26; ++i) {
            if (nx[root][i] == -1)
                nx[root][i] = root;
            else {
                fail[nx[root][i]] = root;
                q.push(nx[root][i]);
            }
        }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                //如果当前节点没有子节点i + 'a'
                //则让这个子节点指向当前节点fail指针对应的子节点
                if (nx[now][i] == -1)
                    nx[now][i] = nx[fail[now]][i];
                else {
                    //如果当前节点有子节点i + 'a'
                    //则让这个子节点的fail指针指向(((它父亲节点)的fail指针指向的那个节点)的对应的子节点)
                    fail[nx[now][i]] = nx[fail[now]][i];
                    q.push(nx[now][i]);
                }
            }
        }
    }
    int query(char *s) {
        memset(vis, 0, sizeof vis);
        int len = strlen(s);
        int now = root;
        int res = 0;
        for (int i = 0; i < len; ++i) {
            now = nx[now][s[i] - 'a'];  //从s[i]开始寻找
            int tmp = now;
            while (tmp != root && !vis[tmp]) {
                //一直向下寻找，直到匹配失败(失败指针指向根或者当前结点已找过)
                res += cnt[tmp];
                //将遍历过后的节点标记，防止重复计算
                vis[tmp] = 1;
                tmp = fail[tmp];
            }
        }
        return res;
    }
} ac;

//给定n个模式串和1一个文本串
//求有多少个模式串在文本串中出现过
int main() {
    while (scanf("%d", &n) != EOF) {
        ac.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            ac.insert(s);
        }
        ac.build();
        scanf("%s", s);
        printf("%d\n", ac.query(s));
    }
    return 0;
}
