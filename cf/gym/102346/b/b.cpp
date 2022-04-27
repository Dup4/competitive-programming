#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, a[N];

int main() {
    scanf("%d", &n);
    int Max = -1;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        Max = max(Max, a[i]);
    }
    puts((a[1] == Max) ? "S" : "N");
    return 0;
}
