#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll N = 1e14;
// const int N = 5e3 + 10;
// int f[N][N];

// int dfs(int i, int j) {
//	if (i <= j) return 1;
//	if (f[i][j] != -1) return f[i][j];
//	for (int x = 1; x <= j; ++x) {
//		if (dfs(i - x, 2 * x) == 0) {
//			return f[i][j] = 1;
//		}
//	}
//	return f[i][j] = 0;
// }

int main() {
    //	memset(f, -1, sizeof f);
    //	f[1][1] = 1;
    //	f[2][1] = 0;
    //	f[2][2] = 1;
    //	f[3][3] = 1;
    //	f[3][2] = 0;
    //	f[3][1] = 0;
    //	f[4][4] = 1;
    //	f[4][3] = 1;
    //	f[4][2] = 1;
    //	f[4][1] = 1;
    //	for (int i = 5; i <= 5000; ++i) {
    //		if (dfs(i, i - 1) == 0) printf("%d\n", i);
    //	printf("%d %d\n", i, dfs(i, i - 1));
    //	}
    int _T;
    scanf("%d", &_T);
    int ans = 0;
    vector<ll> vec;
    vec.push_back(2);
    vec.push_back(3);
    map<ll, int> mp;
    mp[2] = mp[3] = 1;
    //	cout << N << endl;
    while (1) {
        ll t = 1ll * vec.end()[-1] + vec.end()[-2];
        if (t > N)
            break;
        vec.push_back(t);
        mp[t] = 1;
        //		cout << t << endl;
    }
    //	for (auto &it : vec) cout << it << endl;
    //	for (auto &it : mp) cout << it.first << " " << it.second << endl;
    while (_T--) {
        ll n;
        scanf("%lld", &n);
        //	if (mp[n] == 1) ++ans;
        if (mp.find(n) == mp.end())
            ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
