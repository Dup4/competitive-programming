#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;

int main() {
    scanf("%d", &n);
    vector<int> vec[N];
    for (int i = 1, a, c; i <= n; ++i) {
        scanf("%d%d", &a, &c);
        vec[c].push_back(a);
    }
    int ok = 1;
    for (auto &it : vec)
        if (!it.empty()) {
            int pre = -2e9;
            for (auto &v : it) {
                if (pre > v) {
                    ok = 0;
                    break;
                }
                pre = v;
            }
        }
    puts(ok ? "YES" : "NO");
    return 0;
}
