#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define db double
db bit[N];

int main() {
    bit[0] = 1;
    for (int i = 1; i < N; ++i) {
        bit[i] = bit[i - 1] * 1.0 / 2;
    }
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF) {
        db res = 0;
        for (int i = 1; i <= n; ++i) {
            int cnt = 0, t = i;
            while (t < k) {
                ++cnt;
                t <<= 1;
            }
            res += 1.0 / n * bit[cnt];
        }
        printf("%.16f\n", res);
    }
    return 0;
}
