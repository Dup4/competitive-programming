#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, a[N], b[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(b, 0, sizeof b);
        int sum = 0, other = 0;
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i];
        b[1] = 1;
        other = a[1];
        for (int i = 2; i <= n; ++i) {
            if (a[1] >= a[i] * 2) {
                other += a[i];
                b[i] = 1;
            }
        }
        if (other > sum / 2) {
            int sze = 0;
            vector<int> vec;
            for (int i = 1; i <= n; ++i) {
                if (b[i]) {
                    ++sze;
                    vec.push_back(i);
                }
            }
            printf("%d\n", sze);
            for (int i = 0; i < sze; ++i) printf("%d%c", vec[i], " \n"[i == sze - 1]);
        } else {
            puts("0");
        }
    }
    return 0;
}
