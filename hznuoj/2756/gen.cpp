#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, a[N][N];
mt19937 rnd(time(0));
int random(int l, int r) {
    return rnd() % (r - l + 1) + l;
}

int main() {
    n = 1e3;
    cout << n << endl;
    for (int i = 1; i <= n; ++i) a[i][i] = 1;
    for (int i = 1; i < n; ++i) {
        a[i][i + 1] = 1;
        a[i + 1][i] = 1;
    }
    a[500][501] = a[501][500] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << a[i][j] << " \n"[j == n];
        }
    }
    return 0;
}
