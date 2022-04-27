#include <bits/stdc++.h>
using namespace std;

#define N 110
int cnt[220];
char s[N];
int C(int n, int m) {
    if (n < m) {
        return 0;
    }
    return n * (n - 1) / 2;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            ++cnt[s[1]];
        }
        int res = 0;
        for (int i = 'a'; i <= 'z'; ++i) {
            int mid = cnt[i] / 2;
            res += C(mid, 2) + C(cnt[i] - mid, 2);
        }
        printf("%d\n", res);
    }
    return 0;
}
