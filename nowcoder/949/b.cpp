#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define ll long long
const ll p = 1e9 + 7;
int n, m;
vector<vector<int>> vec;
ll sum[N];
void add(ll &x, ll y) {
    x += y;
    if (x >= p)
        x -= p;
}

int main() {
    vec.clear();
    vec.resize(1010);
    vec[1].push_back(1);
    sum[1] = 1;
    vec[2].push_back(2);
    vec[2].push_back(2);
    sum[2] = 5;
    for (int i = 3; i <= 1000; ++i) {
        ll tot = 2 * i;
        vec[i].push_back(i);
        for (int j = 0, sze = (int)vec[i - 1].size(); j < sze - 1; ++j) {
            ll now = (vec[i - 1][j] + vec[i - 1][j + 1]) % p;
            vec[i].push_back(now);
            add(tot, now);
        }
        vec[i].push_back(i);
        sum[i] = tot;
        add(sum[i], sum[i - 1]);
    }
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1, x, y; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            printf("%lld\n", (sum[y] - sum[x - 1] + p) % p);
        }
    }
    return 0;
}
