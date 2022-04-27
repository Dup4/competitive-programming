#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5 + 10;
struct edge {
    int to;
    ll capacity, cost, rev;
    edge() {}
    edge(int to, ll _capacity, ll _cost, ll _rev) : to(to), capacity(_capacity), cost(_cost), rev(_rev) {}
};

//时间复杂度O(F*ElogV)(F是流量, E是边数, V是顶点数)
struct Min_Cost_Max_Flow {
    ll V, H[N + 5], dis[N + 5], PreV[N + 5], PreE[N + 5];
    vector<vector<edge>> G;

    //调用前初始化
    void Init() {
        G.clear();
        G.resize(N + 10);
    }

    //加边
    void addedge(int from, int to, ll cap, ll cost) {
        G[from].push_back(edge(to, cap, cost, G[to].size()));
        G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
    }

    // flow是自己传进去的变量，就是最后的最大流，返回的是最小费用
    ll Min_cost_max_flow(int s, int t, ll f, ll &flow) {
        ll res = 0;
        fill(H, H + 1 + V, 0);
        while (f) {
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
            fill(dis, dis + 1 + V, INF);
            dis[s] = 0;
            q.push(pair<ll, int>(0, s));
            while (!q.empty()) {
                pair<int, int> now = q.top();
                q.pop();
                int v = now.second;
                if (dis[v] < now.first)
                    continue;
                for (int i = 0, sze = (int)G[v].size(); i < sze; ++i) {
                    edge &e = G[v][i];
                    if (e.capacity > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
                        dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
                        PreV[e.to] = v;
                        PreE[e.to] = i;
                        q.push(pair<ll, int>(dis[e.to], e.to));
                    }
                }
            }
            if (dis[t] == INF)
                break;
            for (int i = 0; i <= V; ++i) H[i] += dis[i];
            ll d = f;
            for (int v = t; v != s; v = PreV[v]) d = min(d, G[PreV[v]][PreE[v]].capacity);
            f -= d;
            flow += d;
            res += d * H[t];
            for (int v = t; v != s; v = PreV[v]) {
                edge &e = G[PreV[v]][PreE[v]];
                e.capacity -= d;
                G[v][e.rev].capacity += d;
            }
        }
        return res;
    }
} MCMF;
int n, W, S, T, m, a[N], b[N], in[N], out[N];
ll flow;

void up(const vector<pII> &vec, int sze, int f, int mid) {
    for (int i = 0; i < sze; ++i) {
        b[i] = ++m;
        if (i)
            MCMF.addedge(b[i - 1], b[i], INF, 0);
    }
    for (int i = 0; i < sze; ++i) {
        pII t = vec[i];
        if (t.se <= mid) {
            MCMF.addedge(out[t.se], b[i], 1, t.fi * f);
        } else {
            MCMF.addedge(b[i], in[t.se], 1, t.fi * -f);
        }
    }
}

void gao(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    gao(l, mid);
    gao(mid + 1, r);
    vector<pII> vec;
    for (int i = l; i <= r; ++i) {
        vec.push_back(pII(a[i], i));
    }
    int sze = r - l + 1;
    sort(vec.begin(), vec.end());
    up(vec, sze, -1, mid);
    reverse(vec.begin(), vec.end());
    up(vec, sze, 1, mid);
}

int main() {
    while (scanf("%d%d", &n, &W) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        S = 0, T = 1;
        m = 1;
        MCMF.Init();
        for (int i = 1; i <= n; ++i) {
            in[i] = ++m;
            out[i] = ++m;
            MCMF.addedge(S, in[i], 1, W);
            MCMF.addedge(S, out[i], 1, 0);
            MCMF.addedge(in[i], T, 1, 0);
        }
        gao(1, n);
        MCMF.V = m + 10;
        flow = 0;
        printf("%lld\n", MCMF.Min_cost_max_flow(S, T, INF, flow));
    }
    return 0;
}
