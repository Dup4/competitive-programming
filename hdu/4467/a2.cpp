#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

typedef long long LL;
int N, M, LIM;
int cl[100005], deg[100005];
LL ans[3];       // 其中ans[0],ans[1],ans[2]表示00、01、11的边的权值总和
LL w[700][700];  // 用来记录特殊点之间的权值关系
int tail;        // 特殊点不会超过2*sqrt(M)个
LL fee[700][2];  // 分别记录特殊点与0点相连的边权和，与1点相连的边权和
int sp[100005];  // hash该节点是否为特殊点
map<LL, LL> mp;

struct Edge {
    int v, f, next;
};
Edge e[500005];
int idx, head[100005];

void insert(int a, int b, int f) {
    e[idx].v = b, e[idx].f = f;
    e[idx].next = head[a];
    head[a] = idx++;
}

void init() {
    for (int i = 1; i <= N; ++i) {
        if (deg[i] >= LIM) {
            sp[i] = tail++;
        }  // 将度大的点离散化到一个较小的区间
    }
    map<LL, LL>::iterator it;
    for (it = mp.begin(); it != mp.end(); ++it) {
        int u = it->first / N + 1, v = it->first % N + 1;
        if (~sp[u] && ~sp[v]) {  // 如果两个点都是特殊点
            w[sp[u]][sp[v]] += it->second;
            w[sp[v]][sp[u]] += it->second;
            fee[sp[u]][cl[v]] += it->second;
            fee[sp[v]][cl[u]] += it->second;
        } else if (!(~sp[u]) && !(~sp[v])) {  // 如果两个点都不是特殊点
            insert(u, v, it->second);         // 有度小的点就需要构边等着以后来暴力了
            insert(v, u, it->second);
        } else if (~sp[u]) {
            fee[sp[u]][cl[v]] += it->second;
            insert(v, u, it->second);
        } else {
            fee[sp[v]][cl[u]] += it->second;
            insert(u, v, it->second);
        }
    }
}

void change(int x) {  // 修改过程
    if (~sp[x]) {     // 如果x是特殊的点
        if (cl[x] == 1) {
            ans[1] -= fee[sp[x]][0], ans[0] += fee[sp[x]][0];
            ans[2] -= fee[sp[x]][1], ans[1] += fee[sp[x]][1];
            for (int i = 0; i < tail; ++i) {
                fee[i][1] -= w[sp[x]][i], fee[i][0] += w[sp[x]][i];
            }
        } else {
            ans[0] -= fee[sp[x]][0], ans[1] += fee[sp[x]][0];
            ans[1] -= fee[sp[x]][1], ans[2] += fee[sp[x]][1];
            for (int i = 0; i < tail; ++i) {
                fee[i][0] -= w[sp[x]][i], fee[i][1] += w[sp[x]][i];
            }
        }
    } else {
        for (int i = head[x]; ~i; i = e[i].next) {
            if (cl[x] == 1) {
                ans[cl[e[i].v] + 1] -= e[i].f, ans[cl[e[i].v]] += e[i].f;
                if (~sp[e[i].v]) {  // 如果连接的点是特殊点
                    fee[sp[e[i].v]][1] -= e[i].f, fee[sp[e[i].v]][0] += e[i].f;
                }
            } else {
                ans[cl[e[i].v]] -= e[i].f, ans[cl[e[i].v] + 1] += e[i].f;
                if (~sp[e[i].v]) {
                    fee[sp[e[i].v]][0] -= e[i].f, fee[sp[e[i].v]][1] += e[i].f;
                }
            }
        }
    }
    cl[x] ^= 1;
}

int main() {
    int a, b, c, ca = 0;
    while (scanf("%d %d", &N, &M) != EOF) {
        LIM = (int)sqrt(1.0 * M);  // LIM就是这样的对度数限制的阀值
        tail = idx = 0;
        mp.clear();
        memset(w, 0, sizeof(w));
        memset(head, 0xff, sizeof(head));
        memset(sp, 0xff, sizeof(sp));
        memset(deg, 0, sizeof(deg));
        memset(ans, 0, sizeof(ans));
        memset(fee, 0, sizeof(fee));
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &cl[i]);  // 获取每个节点的原始颜色
        }
        for (int i = 1; i <= M; ++i) {
            scanf("%d %d %d", &a, &b, &c);
            if (a > b)
                swap(a, b);                      // 始终保持a < b，这样才能把所有相同的边合并
            mp[1LL * (a - 1) * N + b - 1] += c;  // 该map用于合并一些边
            ans[cl[a] + cl[b]] += c;
            ++deg[a], ++deg[b];
        }
        init();
        int Q;
        char op[10];
        scanf("%d", &Q);
        printf("Case %d:\n", ++ca);
        while (Q--) {
            scanf("%s", op);
            if (op[0] == 'A') {
                scanf("%d %d", &a, &b);
                // 查询是愉悦的
                printf("%lld\n", ans[a + b]);
            } else {
                scanf("%d", &a);
                change(a);  // 修改是痛苦的
            }
        }
    }
    return 0;
}
