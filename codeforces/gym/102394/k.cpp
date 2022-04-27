#include <bits/stdc++.h>

using namespace std;

using db = double;

const int N = 1e5 + 10;

int n, k;
db w[N];

int main() {
    while (cin >> n >> k) {
        db sum = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> w[i];
            sum += w[i];
        }
        while (k--) {
            for (int i = 1; i <= n; ++i) {
                w[i] += w[i] / sum;
            }
            sum = 0;
            for (int i = 1; i <= n; ++i) {
                sum += w[i];
            }
        }
        for (int i = 1; i <= n; ++i) {
            cout << w[i] << " \n"[i == n];
        }
    }
    return 0;
}
