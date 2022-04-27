#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
list<int> A[N], B[N];
int n, q;

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            A[i].clear();
            A[i].push_front(i);
            B[i].clear();
            B[i].push_front(i);
        }
        for (int i = 1, x, y; i <= q; ++i) {
            scanf("%d%d", &x, &y);
            A[x].splice(A[x].end(), A[y]);
            B[y].splice(B[y].end(), B[x]);
            swap(B[x], B[y]);
            //逆序
            swap(A[x], B[x]);
        }
        printf("%d", (int)A[1].size());
        for (auto &it : A[1]) printf(" %d", it);
        puts("");
    }
    return 0;
}
