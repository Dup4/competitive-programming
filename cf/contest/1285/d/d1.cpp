#include <bits/stdc++.h>
using namespace std;
vector<int> vec;
int n;
int gao(int cur, vector<int> vec) {
    if (cur < 0)
        return 0;
    int cnt[2] = {0, 0};
    for (auto &it : vec) {
        ++cnt[(it >> cur) & 1];
    }
    if (cnt[0] == 0 || cnt[1] == 0)
        return gao(cur - 1, vec);
    else {
        vector<int> v[2];
        for (auto &it : vec) {
            v[(it >> cur) & 1].push_back(it);
        }
        return (1 << cur) | min(gao(cur - 1, v[0]), gao(cur - 1, v[1]));
    }
}

void run() {
    vec.clear();
    vec.resize(n);
    for (auto &it : vec) cin >> it;
    cout << gao(30, vec) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
