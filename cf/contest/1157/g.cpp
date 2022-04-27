#include <bits/stdc++.h>
using namespace std;

#define N 210
int n, m;
vector<bitset<N> > a, b;
bitset<N> row, column, tmp, one;

void print() {
    puts("YES");
    for (int i = 1; i <= n; ++i) {
        printf("%d", (int)row[i]);
    }
    puts("");
    for (int i = 1; i <= m; ++i) {
        printf("%d", (int)column[i]);
    }
    puts("");
}

bool ok() {
    row.reset();
    column = a[1] ^ b[1];
    for (int i = 2; i <= n; ++i) {
        row[i] = a[i][1] ^ b[i][1] ^ column[1];
        tmp.reset();
        tmp = a[i] ^ column;
        if (row[i]) {
            tmp ^= one;
        }
        if (tmp != b[i]) {
            return false;
        }
    }
    return true;
}

void work() {
    if (ok()) {
        print();
        return;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            b[i].reset(j);
            if (ok()) {
                print();
                return;
            }
        }
    }
    puts("NO");
    return;
}

void init() {
    a.resize(n + 1);
    b.resize(n + 1);
    one.reset();
    for (int i = 1; i <= m; ++i) {
        one.set(i);
    }
    for (int i = 1; i <= n; ++i) {
        a[i].reset();
        b[i].reset();
        for (int j = 1; j <= m; ++j) {
            b[i].set(j);
        }
    }
}
int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1, x; j <= m; ++j) {
                scanf("%d", &x);
                if (x) {
                    a[i].set(j);
                }
            }
        }
        work();
    }
    return 0;
}
