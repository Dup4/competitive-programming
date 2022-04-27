#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, d, x[N][N];

int dis(int i, int j) {
    int res = 0;
    for (int o = 1; o <= d; ++o) {
        res += (x[i][o] - x[j][o]) * (x[i][o] - x[j][o]);
    }
    return res;
}

int main() {
    set<int> se;
    se.insert(0);
    for (int i = 1; i <= 30000; ++i) {
        se.insert(i * i);
    }
    while (scanf("%d%d", &n, &d) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= d; ++j) {
                scanf("%d", x[i] + j);
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                int Dis = dis(i, j);
                if (se.count(Dis)) {
                    ++res;
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
