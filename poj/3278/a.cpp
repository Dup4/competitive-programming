#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 2e5 + 5, INF = 0x3f3f3f3f;
int n, k;
int ans;
int v[maxn];

struct node {
    int v, step;
};

bool ok(int x) {
    if (x < 0 || x > maxn)
        return false;
    return true;
}

void bfs() {
    memset(v, 0, sizeof v);
    queue<node> q;
    node tmp;
    tmp.v = n;
    tmp.step = 0;
    q.push(tmp);
    v[n] = 1;
    while (!q.empty()) {
        node u = q.front(), V;
        q.pop();
        if (u.v == k) {
            ans = u.step;
            return;
        }
        V.step = u.step + 1;
        V.v = u.v + 1;
        if (ok(V.v) && v[V.v] == 0) {
            q.push(V);
            v[V.v] = 1;
        }
        V.v = u.v - 1;
        if (ok(V.v) && v[V.v] == 0) {
            q.push(V);
            v[V.v] = 1;
        }
        V.v = u.v * 2;
        if (ok(V.v) && v[V.v] == 0) {
            q.push(V);
            v[V.v] = 1;
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    ans = INF;
    bfs();
    cout << ans << endl;
}
