#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
class MinCost {
public:
    int findMinCost(string A, int n, string B, int m, int c0, int c1, int c2) {
        vector<vector<int>> f(n + 5, vector<int>(m + 5, INF));
        f[0][0] = 0;
        for (int i = 1; i <= n; ++i) f[i][0] = c1 * i;
        for (int i = 1; i <= m; ++i) f[0][i] = c0 * i;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char a = A[i - 1], b = B[j - 1];
                f[i][j] = f[i - 1][j - 1] + ((a != b) * c2);
                f[i][j] = min(f[i][j], f[i][j - 1] + c0);
                f[i][j] = min(f[i][j], f[i - 1][j] + c1);
            }
        }
        return f[n][m];
    }
};

int main() {
    string A, B;
    int c0, c1, c2;
    cin >> A >> B >> c0 >> c1 >> c2;
    int n = A.size(), m = B.size();
    cout << (new MinCost())->findMinCost(A, n, B, m, c0, c1, c2) << endl;
    return 0;
}
