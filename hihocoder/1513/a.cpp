#include <bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10;
bitset<N> b[N][5];
int n;
struct node {
    int g[5], id;
    void scan(int _id) {
        id = _id;
        for (int i = 0; i < 5; ++i) scanf("%d", g + i);
    }
} a[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) a[i].scan(i);
        for (int i = 0; i < 5; ++i) {
            sort(a + 1, a + 1 + n, [&](const node &x, const node &y) {
                return x.g[i] < y.g[i];
            });
            for (int j = 1; j <= n; ++j) {
                int id = a[j].id;
                if (j == 1)
                    b[id][i].reset();
                else {
                    int pre = a[j - 1].id;
                    b[id][i] = b[pre][i];
                    b[id][i][pre] = 1;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < 5; ++j) b[i][0] &= b[i][j];
            printf("%d\n", b[i][0].count());
        }
    }
    return 0;
}
