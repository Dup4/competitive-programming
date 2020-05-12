#include <bits/stdc++.h>

using namespace std;

const int N = 2e2 + 10, INF = 0x3f3f3f3f;

#define dbg(x...)             \
    do {                      \
        cout << #x << " -> "; \
        err(x);               \
    } while (0)

void err() {
    cout << endl;
}

template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}

struct E {
    int a, b, x, id, op;
    E() {}

    E(int a, int b, int x, int id, int op) : a(a), b(b), x(x), id(id), op(op) {}

    bool operator<(const E& other) const { return x < other.x; }
};

struct node {
    int id, x;
    node() {}

    node(int id, int x) : id(id), x(x) {}

    bool operator<(const node& other) const { return x < other.x; }
};

int n, m, top;
int temp[N], res[N];
int G[N][N], _G[N][N];
int id[N];
vector<E> Q;
vector<node> vec;

void gao() {
    // T = 0 <= x
    for (int i = 1; i <= n; ++i) {
        vec.push_back(node(i, temp[i]));
    }
    sort(vec.begin(), vec.end());
    sort(Q.begin(), Q.end());

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            G[i][j] = _G[i][j];
        }
    }
    int pos = -1;
    for (auto it : Q) {
        while (pos < n && vec[pos + 1].x <= id[it.x]) {
            pos++;
            int k = vec[pos].id;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
        if (it.op == 0)
            res[it.id] = G[it.a][it.b];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            G[i][j] = _G[i][j];
        }
    }
    // T = 1 >= x
    reverse(vec.begin(), vec.end());
    reverse(id + 1, id + 1 + top);
    pos = -1;
    for (auto it : Q) {
        // dbg(it.id);
        while (pos < n && vec[pos + 1].x >= id[it.x]) {
            pos++;
            int k = vec[pos].id;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
        if (it.op == 1)
            res[it.id] = G[it.a][it.b];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(_G, INF, sizeof _G);
    for (int i = 1; i <= n; ++i) {
        _G[i][i] = 0;
    }
    set<int> se;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", temp + i);
        se.insert(temp[i]);
    }
    for (auto it : se) {
        id[++top] = it;
    }
    for (int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        _G[u][v] = _G[v][u] = w;
    }
    int q;
    scanf("%d", &q);
    for (int i = 1, a, b, x, t; i <= q; ++i) {
        scanf("%d %d %d %d", &a, &b, &x, &t);
        if (x > top)
            x = top;
        Q.push_back(E(a, b, x, i, t));
    }
    gao();
    for (int i = 1; i <= q; ++i) {
        if (res[i] == INF) {
            res[i] = -1;
        }
        printf("%d\n", res[i]);
    }
    return 0;
}
