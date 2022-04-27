#include <bits/stdc++.h>
using namespace std;

#define N 10010
int n, m, res;
int b[50010][300];

bool same(int x, int y) {
    for (int i = 1; i <= n; ++i) {
        if (b[x][i] != b[y][i]) {
            return false;
        }
    }
    return true;
}

void DFS(int id) {
    for (int i = 0; i < m; ++i) {
        if (same(i, id)) {
            return;
        }
    }
    ++res;
    int nid = ++m;
    if (n % 2 == 0) {
        int mid = n / 2;
        for (int i = 1; i <= mid; ++i) {
            b[nid][i] = b[id][i + mid];
        }
        for (int i = mid + 1; i <= n; ++i) {
            b[nid][i] = b[id][i - mid];
        }
    } else {
        int mid = (n + 1) / 2;
        for (int i = 1; i < mid; ++i) {
            b[nid][i] = b[id][i + mid];
        }
        b[nid][mid] = b[id][mid];
        for (int i = mid + 1; i <= n; ++i) {
            b[nid][i] = b[id][i - mid];
        }
    }
    DFS(nid);
    nid = ++m;
    for (int i = 1; i <= n; ++i) {
        if (i & 1) {
            if (i == n) {
                b[nid][i] = b[id][i];
            } else {
                b[nid][i] = b[id][i + 1];
            }
        } else {
            b[nid][i] = b[id][i - 1];
        }
    }
    DFS(nid);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", b[0] + i);
        }
        m = 0;
        res = 0;
        DFS(0);
        printf("%d\n", res);
    }
    return 0;
}
