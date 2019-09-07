#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
using ll = long long;
using db = double;
using pii = pair<int, int>;

const int N = 1e3 + 10;

struct node {
    int x, y;

    node() {}

    node(int x, int y) : x(x), y(y) {}

    void input() {
        scanf("%d %d", &x, &y);
        x <<= 1, y <<= 1;
    }

    bool operator==(const node &other) const {
        return x == other.x && y == other.y;
    }
} a[N];

int n;
map<pii, int> mp;

void RUN() {
    while (scanf("%d", &n) != EOF) {
        mp.clear();
        for (int i = 1; i <= n; ++i) {
            a[i].input();
            mp[pii(a[i].x, a[i].y)]++;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (a[i] == a[j]) continue;
                mp[pii((a[i].x + a[j].x) / 2, (a[i].y + a[j].y) / 2)] += 2;
            }
        }
        int res = 0;
        for (auto it : mp) {
            res = max(res, it.second);
        }
        printf("%d\n", n - res);
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    RUN();

#ifdef LOCAL_JUDGE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
