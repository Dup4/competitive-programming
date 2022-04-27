#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second
int n, m;

void put(pii x) {
    printf("%d %d\n", x.fi, x.se);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        if (n > 3 * m + 1 || m > 3 * n + 1)
            puts("NO");
        else {
            puts("YES");
            if (n == m) {
                for (int i = 1; i <= 2 * n; ++i) {
                    printf("1 %d\n", i);
                }
            } else {
                //黑多白少
                if (n > m) {
                    for (int i = 1; i <= m + 1 + m; ++i) {
                        put(pii(i, 4));
                    }
                    n -= m + 1;
                    int pos = 2;
                    while (n) {
                        if (n) {
                            put(pii(pos, 3));
                            --n;
                        }
                        if (n) {
                            put(pii(pos, 5));
                            --n;
                        }
                        pos += 2;
                    }
                } else {
                    for (int i = 1; i <= n + 1 + n; ++i) {
                        put(pii(i, 3));
                    }
                    m -= n + 1;
                    int pos = 2;
                    while (m) {
                        if (m) {
                            put(pii(pos, 2));
                            --m;
                        }
                        if (m) {
                            put(pii(pos, 4));
                            --m;
                        }
                        pos += 2;
                    }
                }
            }
        }
    }
    return 0;
}
