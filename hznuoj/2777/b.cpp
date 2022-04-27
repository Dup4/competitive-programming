#include <bits/stdc++.h>

using namespace std;

#define dbg(x...)             \
    do {                      \
        cout << #x << " -> "; \
        err(x);               \
    } while (0)

void err() {
    cout << endl;
}

template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}

#define endl "\n"
#define all(A) A.begin(), A.end()
using ll = long long;
using db = double;
using pII = pair<int, int>;

const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 2e5 + 10;

ll n, m;
string op;

void RUN() {
    cin >> n >> m;
    bool F = true;
    for (int i = 1, x; i <= m; ++i) {
        cin >> op;
        if (op == "Add") {
            cin >> x;
            n += x;
        } else if (op == "Sub") {
            cin >> x;
            n -= x;
        } else {
            if (F) {
                cout << n << endl;
            } else {
                cout << "fake news!" << endl;
            }
        }
        cout << n << endl;
        if (n < 0) {
            F = false;
        }
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cout << fixed << setprecision(20);

    RUN();

#ifdef LOCAL_JUDGE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
