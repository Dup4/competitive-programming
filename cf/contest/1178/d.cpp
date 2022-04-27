#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define pii pair<int, int>
#define fi first
#define se second
int n;

bool isprime(int x) {
    for (int i = 2; i < x; ++i) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        int tot = n;
        for (int i = tot;; ++i) {
            if (isprime(i)) {
                tot = i;
                break;
            }
        }
        vector<pii> vec;
        for (int i = 2; i <= n; ++i) vec.push_back(pii(i - 1, i));
        vec.push_back(pii(1, n));
        int remind = tot - n;
        int pos = n / 2 + 1;
        for (int i = 1; i <= remind; ++i) {
            vec.push_back(pii(i, pos));
            ++pos;
        }
        printf("%d\n", tot);
        for (auto it : vec) printf("%d %d\n", it.fi, it.se);
    }
    return 0;
}
