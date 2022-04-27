#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, a[N], b[N];
int Sta[N << 1], top;
int L[N], R[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            b[a[i]] = i;
        }
        top = 0;
        Sta[++top] = n + 1;
        a[n + 1] = n + 1, a[0] = n + 1;
        for (int i = n; i >= 1; --i) {
            while (a[i] > a[Sta[top]]) {
                --top;
            }
            R[i] = Sta[top] - 1;
            Sta[++top] = i;
        }
        top = 0;
        Sta[++top] = 0;
        for (int i = 1; i <= n; ++i) {
            while (a[i] > a[Sta[top]]) {
                --top;
            }
            L[i] = Sta[top] + 1;
            Sta[++top] = i;
        }
        //	for (int i = 1; i <= n; ++i) {
        //		printf("%d %d %d\n", i, L[i], R[i]);
        //	}
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            int l = L[i], r = R[i];
            if (i - l < r - i) {
                for (int j = l; j < i; ++j) {
                    int t = b[a[i] - a[j]];
                    if (t > i && t <= r) {
                        ++res;
                    }
                }
            } else {
                for (int j = i + 1; j <= r; ++j) {
                    int t = b[a[i] - a[j]];
                    if (t < i && t >= l) {
                        ++res;
                    }
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
