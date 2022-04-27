/*
 * Author:  heyuhhh
 * Created Time:  2020/4/8 23:33:45
 */
#include <assert.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define MP make_pair
#define fi first
#define se second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define INF 0x3f3f3f3f
#define Local
#ifdef Local
#define dbg(args...)             \
    do {                         \
        cout << #args << " -> "; \
        err(args);               \
    } while (0)
void err() {
    std::cout << std::endl;
}
template <typename T, typename... Args>
void err(T a, Args... args) {
    std::cout << a << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) std::cout << v << ' ';
    err(args...);
}
#else
#define dbg(...)
#endif
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
// head
const int N = 1e6 + 5;

int n;
int pri[N], tot;
bool vis[N];
int ans[N];

void init() {
    pri[++tot] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri[++tot] = i;
            ans[tot] = 1;
            for (ll j = 1ll * i * i; j <= n; j += i) vis[j] = true;
        }
    }
}

void run() {
    cin >> n;
    init();
    int now = 2;
    for (int i = tot + 1, j; i <= n; i = j, ++now) {
        j = i;
        for (int k = 2; j <= n && k <= now; k++) {
            if (1ll * k * now > n)
                break;
            ans[j++] = now;
        }
    }
    for (int i = 2; i <= n; i++) cout << ans[i] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
