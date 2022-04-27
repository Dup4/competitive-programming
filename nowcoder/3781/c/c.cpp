#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> vec;
vector<int> del, tmp;
int n, x;
ll w, Max;

void dfs(int cur, ll sum) {
    if (sum > w)
        return;
    if (sum == w) {
        Max = sum;
        del = tmp;
        return;
    }
    if (cur >= (int)vec.size()) {
        if (sum > Max) {
            Max = sum;
            del = tmp;
        }
        return;
    }
    dfs(cur + 1, sum);
    if (Max == w)
        return;
    tmp[cur] = 1;
    dfs(cur + 1, sum + vec[cur]);
    tmp[cur] = 0;
}

void gao() {
    if (vec.end()[-1] > w) {
        puts("No");
        return;
    }
    if (x >= n) {
        puts("Yes");
        return;
    }
    while (!vec.empty()) {
        if (!x) {
            puts("No");
            return;
        }
        if (accumulate(vec.begin(), vec.end(), 0ll) <= w) {
            puts("Yes");
            return;
        }
        tmp.clear();
        tmp.resize(vec.size());
        del = tmp;
        Max = 0;
        dfs(0, 0);
        --x;
        tmp.clear();
        for (int i = 0; i < (int)vec.size(); ++i) {
            if (del[i] == 0)
                tmp.push_back(vec[i]);
        }
        vec = tmp;
    }
    puts("Yes");
}

int main() {
    int _T;
    cin >> _T;
    while (_T--) {
        scanf("%d%d%lld", &n, &x, &w);
        x = min(x, n);
        vec.clear();
        vec.resize(n);
        for (auto &it : vec) cin >> it;
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        gao();
    }
    return 0;
}
