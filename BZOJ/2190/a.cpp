#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define N 40010
int prime[N], phi[N];
bool check[N];
 
void init()
{
    memset(check, false, sizeof check);
    int cnt = 0;
    phi[1] = 1;
    for (int i = 2; i < N; ++i)
    {
        if (!check[i])
        {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt; ++j)
        {
            if (i * prime[j] > N) break;
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
 
void Run()
{
    init();
    int n; cin >> n;
    if (n == 1)
    {
        cout << 0 << "\n";
        return;
    }
    ll res = 0;
    for (int i = 2; i < n; ++i)
        res += phi[i];
    res = res * 2 + 3;
    cout << res << "\n";
}
 
int main()
{
    #ifdef LOCAL
        freopen("Test.in", "r", stdin);
    #endif 
 
    Run();
    return 0;
}
