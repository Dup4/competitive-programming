#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

int n;
int arr[maxn << 1];
int sum[maxn << 1];

int main() {
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", arr + i);
            arr[i + n] = arr[i];
        }
        sum[n << 1 | 1] = 0;
        for (int i = n * 2; i >= 1; --i) {
            if (arr[i] == 1) {
                sum[i] = min(n, sum[i + 1] + 1);
            } else {
                sum[i] = 0;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (arr[i] != 1) {
                puts("First");
            } else {
                if (sum[i] == n) {
                    puts(n % 2 == 1 ? "First" : "Second");
                    continue;
                }
                puts(sum[i] % 2 == 1 ? "Second" : "First");
            }
        }
    }
    return 0;
}
