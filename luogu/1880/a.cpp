#include <bits/stdc++.h>
using namespace std;
const int N = 2e2 + 10, INF = 0x3f3f3f3f;
int n, a[N], S[N], Min[N][N], Max[N][N], PMin[N][N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        a[i + n] = a[i];
    }
    for (int i = 1; i <= n * 2; ++i) S[i] = S[i - 1] + a[i], PMin[i][i] = i;
    for (int len = 2; len <= n * 2; ++len) {
        for (int i = 1; i + len - 1 <= n * 2; ++i) {
            int j = i + len - 1;
            Min[i][j] = INF;
            Max[i][j] = max(Max[i][i] + Max[i + 1][j], Max[i][j - 1] + Max[j][j]) + S[j] - S[i - 1];
            for (int k = PMin[i][j - 1]; k <= PMin[i + 1][j]; ++k) {
                int V = Min[i][k] + Min[k + 1][j] + S[j] - S[i - 1];
                if (V < Min[i][j]) {
                    Min[i][j] = V;
                    PMin[i][j] = k;
                } else if (V == Min[i][j]) {
                    PMin[i][j] = max(PMin[i][j], k);
                }
            }
        }
    }
    int resMin = INF, resMax = 0;
    for (int i = 1; i <= n; ++i) {
        resMin = min(resMin, Min[i][i + n - 1]);
        resMax = max(resMax, Max[i][i + n - 1]);
    }
    printf("%d\n%d\n", resMin, resMax);
    return 0;
}
