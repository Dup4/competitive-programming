#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
int check[N], f[N];
void init() {
    memset(check, 0, sizeof check);
    int cnt = 0;
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            f[i] = ++cnt;
        }
        for (int j = i; j < N; j += i) {
            if (!check[j]) {
                check[j] = 1;
                f[j] = cnt;
            }
        }
    }
}

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        for (int i = 2; i <= n; ++i) {
            printf("%d%c", f[i], " \n"[i == n]);
        }
    }
    return 0;
}
