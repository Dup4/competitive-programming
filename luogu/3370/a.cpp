#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;

#define N 100010
//拉链法
// cc_hash_table<string, int> h;

//探测法
gp_hash_table<string, int> h;
int n;
char s[N];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            ++h[s + 1];
        }
        printf("%d\n", (int)h.size());
    }
    return 0;
}
