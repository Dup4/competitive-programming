#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, q, a[N], b[N], idA[N], idB[N];

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            a[i] %= 2;
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", b + i);
            b[i] %= 2;
        }
        idA[1] = 1;
        idB[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i] == a[i - 1]) {
                idA[i] = idA[i - 1];
            } else {
                idA[i] = idA[i - 1] + 1;
            }
            if (b[i] == b[i - 1]) {
                idB[i] = idB[i - 1];
            } else {
                idB[i] = idB[i - 1] + 1;
            }
            //	cout << idA[i] << " " << idB[i] << endl;
        }
        int x[2], y[2];
        while (q--) {
            scanf("%d%d%d%d", x, y, x + 1, y + 1);
            if (idA[x[0]] == idA[x[1]] && idB[y[0]] == idB[y[1]]) {
                puts("YES");
            } else {
                puts("NO");
            }
        }
    }
    return 0;
}
