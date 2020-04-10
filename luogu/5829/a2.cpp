#include <bits/stdc++.h>
const int MaxN = 1000000 + 5, MaxM = 100000 + 5;
const int MaxLog = 20;

int N, M;
char S[MaxN];
int Fail[MaxN];
int Fa[MaxLog + 1][MaxN], Dep[MaxN];

void init() {
  scanf("%s", S + 1);
  N = strlen(S + 1);
  scanf("%d", &M);
}

  int getLca(int u, int v) {
  if (Dep[u] < Dep[v]) std::swap(u, v);
  int d = Dep[u] - Dep[v];
  for (int i = MaxLog; i >= 0; --i)
    if (d & (1 << i)) u = Fa[i][u];
  if (u == v) return u;
  for (int i = MaxLog; i >= 0; --i)
    if (Fa[i][u] != Fa[i][v]) {
      u = Fa[i][u];
      v = Fa[i][v];
    }
  return Fa[0][u];
}

void solve() {
  for (int i = 2, j = 0; i <= N; ++i) {
    while (j > 0 && S[i] != S[j + 1]) j = Fail[j];
    if (S[i] == S[j + 1]) j++;
    Fail[i] = j;
	printf("%d%c", Fail[i], " \n"[i == N]);
  }
  return;
  for (int u = 1; u <= N; ++u) {
    Fa[0][u] = Fail[u];
    Dep[u] = Dep[Fail[u]] + 1;
    for (int i = 1; (1 << i) <= Dep[u]; ++i)
      Fa[i][u] = Fa[i - 1][Fa[i - 1][u]];
  }
  for (int q = 1; q <= M; ++q) {
    int x, y;
    scanf("%d %d", &x, &y);
    int l = getLca(x, y);
    if (l == x || l == y) printf("%d\n", Fa[0][l]);
    else printf("%d\n", l);
  }
}

int main() {
  init();
  solve();
  return 0;
}
