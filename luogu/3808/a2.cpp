#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define ALP 26
char s[N];
int n;

struct ACAM {
    struct node {
        int nx[ALP], fail;
        int cnt;
        bool vis;
        node() {
            memset(nx, -1, sizeof nx);
            cnt = 0;
            vis = 0;
        }
    } t[N];
    int root, tot;
    int que[N], ql, qr;
    //节点从1开始
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void init() {
        tot = 0;
        root = newnode();
    }
    void insert(char *s) {
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; ++i) {
            if (t[now].nx[s[i] - 'a'] == -1)
                t[now].nx[s[i] - 'a'] = newnode();
            now = t[now].nx[s[i] - 'a'];
        }
        //表示以该结点结尾的模式串数量
        ++t[now].cnt;
    }
    void build() {
        ql = 1, qr = 0;
        t[root].fail = root;
        //将第二层出现过的字母扔进队列，并将fail指向根
        //对于没出现过的字母，直接将该字母的下一个节点指向根
        for (int i = 0; i < ALP; ++i) {
            if (t[root].nx[i] == -1) {
                t[root].nx[i] = root;
            } else {
                t[t[root].nx[i]].fail = root;
                que[++qr] = t[root].nx[i];
            }
        }
        while (ql <= qr) {
            int now = que[ql++];
            for (int i = 0; i < ALP; ++i) {
                //如果当前节点没有子节点i + 'a'
                //则让这个子节点指向当前节点fail指针对应的子节点
                if (t[now].nx[i] == -1) {
                    t[now].nx[i] = t[t[now].fail].nx[i];
                } else {
                    //如果当前节点有子节点i + 'a'
                    //则让这个子节点的fail指针指向(((它父亲节点)的fail指针指向的那个节点)的对应的子节点)
                    t[t[now].nx[i]].fail = t[t[now].fail].nx[i];
                    que[++qr] = t[now].nx[i];
                }
            }
        }
    }
    int query(char *s) {
        int len = strlen(s);
        int now = root;
        int res = 0;
        for (int i = 0; i < len; ++i) {
            //查找以s[i]结尾的模式串数量
            now = t[now].nx[s[i] - 'a'];
            int tmp = now;
            while (tmp != root && !t[tmp].vis) {
                //一直向下寻找，直到匹配失败(失败指针指向根或者当前结点已找过)
                res += t[tmp].cnt;
                //将遍历过后的节点标记，防止重复计算
                t[tmp].vis = 1;
                tmp = t[tmp].fail;
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
