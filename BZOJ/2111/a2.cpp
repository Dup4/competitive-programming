#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
#define MAX 1000100
#define ls (u << 1)
#define rs (u << 1 | 1)
inline int read() {
    int x = 0;
    bool t = false;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-')
        t = true, ch = getchar();
    while (ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
    return t ? -x : x;
}
int n, MOD;
struct Int {
    int x, y;
} jc[MAX], jv[MAX], inv[MAX];
Int operator*(Int a, Int b) {
    return (Int){(int)(1ll * a.x * b.x % MOD), a.y + b.y};
}
Int operator*(Int a, int b) {
    b %= MOD;
    if (!b)
        a.y += 1;
    else
        a.x = 1ll * a.x * b % MOD;
    return a;
}
int sz[MAX << 2];
Int C(int n, int m) {
    return jc[n] * jv[m] * jv[n - m];
}
void dfs(int u) {
    sz[u] = 1;
    if (ls <= n)
        dfs(ls), sz[u] += sz[ls];
    if (rs <= n)
        dfs(rs), sz[u] += sz[rs];
}
Int DFS(int u) {
    if (u > n)
        return (Int){1, 0};
    return DFS(ls) * DFS(rs) * C(sz[u] - 1, sz[ls]);
}
void output(Int a) {
    if (a.y)
        puts("0");
    else
        printf("%d\n", a.x);
}
int main() {
    n = read();
    MOD = read();
    jc[0] = jv[0] = inv[0] = inv[1] = (Int){1, 0};
    for (int i = 2; i <= n; ++i)
        if (i < MOD)
            inv[i] = inv[MOD % i] * (MOD - MOD / i);
        else if (i % MOD)
            inv[i] = inv[i - MOD];
        else
            inv[i].y = 1, inv[i].x = 1;
    for (int i = 1; i <= n; ++i) inv[i].y *= -1;
    for (int i = 1; i <= n; ++i) jc[i] = jc[i - 1] * i;
    for (int i = 1; i <= n; ++i) jv[i] = jv[i - 1] * inv[i];
    dfs(1);
    output(DFS(1));
    return 0;
}
