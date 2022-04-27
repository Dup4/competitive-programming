#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int pri[N], check[N], ans[N];
void sieve() {
    memset(check, 0, sizeof check);
    for (int i = 2; i < N; ++i) {
        if (!check[i]) {
            pri[++*pri] = i;
        }
        for (int j = 1; j <= *pri; ++j) {
            if (1ll * i * pri[j] >= N)
                break;
            check[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

int get(int x) {
    int y = sqrt(x);
    for (int i = y - 5; i <= y + 5; ++i) {
        if (i * i == x)
            return i;
    }
    return N + 10;
}

int main() {
    sieve();
    memset(ans, 0, sizeof ans);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                int now = i * i + j * j + k * k;
                if (now > N * N)
                    break;
                int x = get(now);
                if (x < N)
                    ++ans[x];
            }
        }
    }
    for (int i = 1; i < N; ++i) {
        printf("%d %d %d\n", i, !check[i], ans[i]);
    }
    return 0;
}
