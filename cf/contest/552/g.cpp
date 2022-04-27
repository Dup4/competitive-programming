#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 10000010
#define INFLL 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f
int n, a[N], b[N];
void work() {
    ll res = INFLL;
    int x, y;
    for (int i = 1; i < N; ++i) {
        int Min = INF;
        for (int j = i; j < N; j += i)
            if (b[j]) {
                if (Min != INF) {
                    if (1ll * Min * j / i < res) {
                        res = 1ll * Min * j / i;
                        x = Min, y = j;
                    }
                    break;
                } else {
                    Min = j;
                    if (b[j] > 1) {
                        if (1ll * j * j / i < res) {
                            res = 1ll * j * j / i;
                            x = j, y = j;
                        }
                        break;
                    }
                }
            }
    }
    for (int i = 1; i <= n; ++i) {
        if (x == a[i]) {
            x = i;
            break;
        }
    }
    for (int i = n; i >= 1; --i) {
        if (y == a[i]) {
            y = i;
            break;
        }
    }
    if (x > y)
        swap(x, y);
    printf("%d %d\n", x, y);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        memset(b, 0, sizeof b);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            ++b[a[i]];
        }
        work();
    }
    return 0;
}
