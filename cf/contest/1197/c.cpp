#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n, k, a[N];

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        ll res = a[n] - a[1];
        vector<int> vec;
        for (int i = 1; i < n; ++i) {
            vec.push_back(a[i] - a[i + 1]);
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < k - 1; ++i) {
            res += vec[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}
