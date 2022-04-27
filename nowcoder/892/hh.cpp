#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, l, r;
int arr[100];
int brr[100];
ll dp[100][10];

int getlen(int x) {
    int len = 0;
    while (x) {
        arr[pos++] = x % 2;
        x >>= 1;
    }
    return len;
}

void Init(int x) {
    int pos = 0;
    while (x) {
        brr[pos++] = x % 2;
        x >>= 1;
    }
}

ll DP(int pos, int cnt, int limit) {
    if (pos == 0)
        return 1ll;
    if (dp[pos][cnt] != -1) {
        return dp[pos][cnt];
    }
    ll ret = 0;
    int L = limit ? arr[pos] : 1;
    if (brr[pos] == 0)
        L = 0;
    for (int i = 0; i <= L; ++i) {
        ret += DFS(pos - 1, i, limit & (L == arr[pos]));
    }
    dp[pos][cnt] = ret;
    return ret;
}

int main() {
    while (~sacnf("%lld %lld %lld", &n, &l, &r)) {
        memset(dp, -1, sizeof dp);
        Init(n);
        int len = getlen(pos);
        ll L = DP(len - 1, )
    }
    return 0;
}
