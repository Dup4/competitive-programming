#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define SZ(x) (int((x).size()))
const int N = 1e4 + 10;
char s[N];
int n;

vector<ll> vec;

void gao(ll x) {
    ll t = vec.back();
    for (int i = SZ(vec) - 2; i >= 0; --i) {
        vec[i + 1] = vec[i + 1] * x - vec[i];
    }
    vec[0] *= x;
    vec.push_back(-t);
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    if (s[1] == 'H')
        vec.push_back(1);
    else
        vec.push_back(-1);
    for (int i = 2; i <= n; ++i) {
        if (s[i] != s[i - 1]) {
            //	cout << (i - 1) * 2 + 1 << endl;
            gao((i - 1) * 2 + 1);
        }
    }
    reverse(vec.begin(), vec.end());
    printf("%d\n", SZ(vec) - 1);
    for (int i = 0; i < SZ(vec); ++i) printf("%lld%c", vec[i], " \n"[i == SZ(vec) - 1]);
    return 0;
}
