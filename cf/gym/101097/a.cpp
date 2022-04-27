#include <bits/stdc++.h>
using namespace std;

int main() {
    for (int n = 1; n <= 10; ++n) {
        for (int m = 1; m <= 10; ++m) {
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    int res = i ^ (n - 1 - i) ^ j ^ (m - 1 - j);
                    if (res == 0) {
                        cnt++;
                    }
                }
            }
            cout << cnt << " ";
        }
        cout << endl;
    }
    return 0;
}
