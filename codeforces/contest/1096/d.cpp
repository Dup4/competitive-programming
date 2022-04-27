#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N];
ll f[5];
char s[N];

int main() {
    char *t = "hard";
    while (scanf("%d", &n) != EOF) {
        scanf("%s", s + 1);
        for (int i = 1; i <= n; ++i) scanf("%d", a + i);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; t[j]; ++j) {
                if (s[i] == t[j]) {
                    if (j == 0)
                        f[j] += a[i];
                    else
                        f[j] = min(f[j] + a[i], f[j - 1]);
                    break;
                }
            }
        }
        printf("%lld\n", f[3]);
    }
    return 0;
}
