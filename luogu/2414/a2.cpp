#include <bits/stdc++.h>
using namespace std;
#define MAX 200000
inline int read() {
    int x = 0, t = 1;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-')
        t = -1, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
    return x * t;
}
char ss[MAX];
int nd[MAX], n, tot;
struct Node {
    int vis[26];
    int fail, fa;
    int lt;
} t[MAX];
void GetFail() {
    queue<int> Q;
    for (int i = 0; i < 26; ++i)
        if (t[0].vis[i])
            Q.push(t[0].vis[i]);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < 26; ++i)
            if (t[u].vis[i])
                t[t[u].vis[i]].fail = t[t[u].fail].vis[i], Q.push(t[u].vis[i]);
            else
                t[u].vis[i] = t[t[u].fail].vis[i];
    }
}
int Query(int x, int y) {
    int ret = 0;
    int now = nd[y];
    while (now) {
        for (int i = now; i; i = t[i].fail)
            if (t[i].lt == x) {
                ++ret;
                break;
            }
        now = t[now].fa;
    }
    return ret;
}
int main() {
    scanf("%s", ss + 1);
    int now = 0;
    for (int i = 1, l = strlen(ss + 1); i <= l; ++i) {
        if (ss[i] >= 'a' && ss[i] <= 'z') {
            if (!t[now].vis[ss[i] - 'a'])
                t[now].vis[ss[i] - 'a'] = ++tot, t[tot].fa = now;
            now = t[now].vis[ss[i] - 'a'];
        }
        if (ss[i] == 'B')
            now = t[now].fa;
        if (ss[i] == 'P') {
            nd[++n] = now;
            t[now].lt = n;
        }
    }
    int Q = read();
    GetFail();
    while (Q--) {
        int x = read(), y = read();
        printf("%d\n", Query(x, y));
    }
    return 0;
}
