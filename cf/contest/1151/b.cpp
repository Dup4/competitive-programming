#include <bits/stdc++.h>
using namespace std;

#define N 510
int n, m;
int a[N][N];
int id[N];

bool ok() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= m; ++j)
            if (a[i][j] != a[i][1]) {
                id[i] = j;
                return 1;
            }
    }
    return 0;
}

void print() {
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", id[i], " \n"[i == n]);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &a[i][j]);
            }
            res ^= a[i][1];
            id[i] = 1;
        }
        if (res == 0) {
            if (ok()) {
                puts("TAK");
                print();
            } else {
                puts("NIE");
            }
        } else {
            puts("TAK");
            print();
        }
    }
    return 0;
}
