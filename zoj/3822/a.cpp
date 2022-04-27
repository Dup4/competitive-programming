#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 60
db f[N][N][N * N];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n > m)
            swap(n, m);
        int sum = n * m;
        f[0][0][0] = 1;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                if (i + j)
                    for (int k = 1; k <= sum; ++k) {
                        db tot;
                        if (i == n && j == m)
                            tot = 0;
                        else
                            tot = f[i][j][k - 1] * (i * j - k + 1) * 1.0 / (sum - k + 1);
                        if (i - 1 >= 0)
                            tot += f[i - 1][j][k - 1] * (n - i + 1) * j * 1.0 / (sum - k + 1);
                        if (j - 1 >= 0)
                            tot += f[i][j - 1][k - 1] * (m - j + 1) * i * 1.0 / (sum - k + 1);
                        if (i - 1 >= 0 && j - 1 >= 0)
                            tot += f[i - 1][j - 1][k - 1] * (n - i + 1) * (m - j + 1) * 1.0 / (sum - k + 1);
                        f[i][j][k] = tot;
                    }
        db res = 0;
        for (int i = 1; i <= sum; ++i) res += f[n][m][i] * i;
        printf("%.10f\n", res);
    }
    return 0;
}
