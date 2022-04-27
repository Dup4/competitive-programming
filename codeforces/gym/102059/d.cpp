#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define pii pair<int, int>
int n, m, l[N], r[N], d[N];
vector<int> G[N], vec[N];

int ord[N];
void pre() {
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (d[i] == 0)
            q.push(i);
    ord[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord[++ord[0]] = u;
        for (auto v : G[u])
            if (--d[v] == 0)
                q.push(v);
    }
}

void Toposort() {
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    for (int i = 1; i <= n; ++i)
        if (d[i] == 0)
            vec[l[i]].push_back(i);
    ord[0] = 0;
    for (auto it : vec[1]) pq.push(pii(r[it], it));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        ord[++ord[0]] = u;
        if (r[u] < ord[0]) {
            puts("-1");
            return;
        }
        for (auto v : G[u])
            if (--d[v] == 0)
                vec[max(ord[0] + 1, l[v])].push_back(v);
        for (auto it : vec[ord[0] + 1]) pq.push(pii(r[it], it));
    }
    if (ord[0] < n)
        puts("-1");
    else
        for (int i = 1; i <= n; ++i) printf("%d\n", ord[i]);
}

void work() {
    pre();
    if (ord[0] < n) {
        puts("-1");
        return;
    }
    /*
    for (int i = n; i >= 1; --i)
    {
            sort(G[i].begin(), G[i].end(), [&](int a, int b) { return r[a] > r[b]; });
            for (auto v : G[i])
            {
                    ++d[v];
                    r[i] = min(r[i], r[v] - 1);
            }
    }
    */
    Toposort();
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            d[i] = 0;
            vec[i].clear();
            scanf("%d%d", l + i, r + i);
        }
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            ++d[v];
        }
        work();
    }
    return 0;
}
