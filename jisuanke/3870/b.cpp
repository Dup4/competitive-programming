#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;

const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;

struct Edge {
    int to, nxt, w;

    Edge() {}

    Edge(int to, int nxt, int w) : to(to), nxt(nxt), w(w) {}
} edge[N * N];

struct qnode {
    int u, w;

    qnode() {}

    qnode(int u, int w) : u(u), w(w) {}

    bool operator<(const qnode &other) const {
        return w > other.w;
    }
};

int n, e, s, k, c, a[N];
int tot;
int head[N];
int dis[N];
bool used[N];
vector<int> vec[2];

void Init() {
    tot = 0;
    memset(head, -1, sizeof head);
}

void addedge(int u, int v, int w) {
    edge[tot] = Edge(v, head[u], w);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], w);
    head[v] = tot++;
}

int gao(const vector<int> &V) {
    for (int i = 1; i <= n; ++i) {
        dis[i] = INF, used[i] = false;
    }
    priority_queue<qnode> pq;
    for (auto it : V) {
        pq.push(qnode(it, 0));
        dis[it] = 0;
    }
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (used[u])
            continue;
        used[u] = true;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to, w = edge[i].w;
            if (!used[v] && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(qnode(v, dis[v]));
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        res = max(res, dis[i]);
    }
    return res;
}

void RUN() {
    scanf("%d %d %d %d %d", &n, &e, &s, &k, &c);
    Init();
    vec[0].clear(), vec[1].clear();
    vec[0].push_back(s);
    for (int i = 1; i <= k; ++i) {
        scanf("%d", a + i);
        vec[1].push_back(a[i]);
    }
    for (int i = 1, u, v, w; i <= e; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addedge(u, v, w);
    }
    int res1 = gao(vec[0]);
    int res2 = gao(vec[1]);
    //    for (int i = 1; i <= k; ++i) {
    //        res2 = min(res2, gao(a[i]));
    //    }
    if (res1 > res2 * c) {
        printf("%d\n", res2);
    } else {
        printf("%d\n", res1);
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    //    ios::sync_with_stdio(false);
    //    cin.tie(nullptr), cout.tie(nullptr);
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        RUN();
    }

#ifdef LOCAL_JUDGE
//    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
