#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, m, b[N];

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= m; ++i) {
            scanf("%d", b + i);
        }
        vector<int> vec;
        for (int i = 1; i <= n; ++i) {
            int x = -1;
            for (int j = 1; j <= m; ++j) {
                if (b[j]) {
                    x = j;
                    break;
                }
            }
            for (int j = 1; j <= m; ++j) {
                if (j - x >= 0)
                    b[j] -= b[j - x];
            }
            vec.push_back(x);
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < n; ++i) printf("%d%c", vec[i], " \n"[i == n - 1]);
    }
    return 0;
}
