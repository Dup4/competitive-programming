#include <bits/stdc++.h>
using namespace std;

#define N 200010
int n, b, a;
int s[N];

int main() {
    while (scanf("%d%d%d", &n, &b, &a) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", s + i);
        }
        int res = 0;
        int x = b, y = a;
        for (int i = 1; i <= n; ++i) {
            res = i;
            if (y == a) {
                --y;
            } else if (x > 0) {
                if (s[i] == 0) {
                    if (y > 0) {
                        --y;
                    } else {
                        --x;
                    }
                } else {
                    --x;
                    ++y;
                }
            } else if (y > 0) {
                --y;
            } else {
                --res;
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
