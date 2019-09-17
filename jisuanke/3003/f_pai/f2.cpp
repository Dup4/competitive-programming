#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e12;
const int DLEN = 12;

struct Num {
  long long a, b;
  Num() {
    a = b = 0;
  }
  Num(int v) {
    a = 0;
    b = v;
  }
  Num(long long v) {
    a = v/MOD;
    b = v%MOD;
  }
  Num(const char s[]) {
    a = b = 0;
    int L = strlen(s);
    for (int i = 0; i < L; i++) {
      b = b*10 + s[i] - '0';
      a = a*10;
      a += b/MOD;
      b %= MOD;
    }
  }
  void output() {
    cout<<a<<b<<endl;
  }
  Num operator *(const int v)const {
    Num res;
    res.b = b;
    res.a = a;
    res.b *= v;
    res.a *= v;
    res.a += res.b/MOD;
    res.b %= MOD;
    return res;
  }
  Num operator +(const Num &v)const {
    Num res;
    res.a = a;
    res.b = b;
    res.a += v.a;
    res.b += v.b;
    res.a += res.b/MOD;
    res.b %= MOD;
    return res;
  }
  Num operator -(const Num &v)const {
    Num res;
    res.a = a;
    res.b = b;
    res.a -= v.a;
    res.b -= v.b;
    if (res.b < 0) {
      res.b += MOD;
      res.a--;
    }
    return res;
  }
  bool operator <(const Num &v)const {
    if (a < v.a) return true;
    return a <= v.a && b < v.b;
  }
};
Num dp[100][100][100];
char str[100];

void dfs(int n, Num k, int id, int Max) {
  if (id == n) return;

  for (int i = 1; i <= Max+1; i++) {
    int nn = max(Max, i);
    if (dp[n][id+1][nn] < k) {
      k = k - dp[n][id+1][nn];
    } else {
      printf("%c", 'A' + i - 1);
      dfs(n, k, id+1, nn);
      return;
    }
  }
}

int main() {

  for (int n = 1; n <= 26; n++) {
    for (int i = n; i >= 1; i--) {
      if (i == n) {
        for (int j = 1; j <= i; j++)
          dp[n][i][j].b = 1LL;
      } else {
        for (int j = 1; j <= i; j++) {
          dp[n][i][j] = dp[n][i+1][j] * j + dp[n][i+1][j+1];
        }
      }
    }
  }
  int T;
  int iCase = 0;
  scanf("%d", &T);
  while (T--) {
    iCase++;
    int n;
    scanf("%d", &n);
    scanf("%s", str);
    Num k = Num(str);
    printf("Case #%d: A", iCase);
    dfs(n, k, 1, 1);
    puts("");
  }
  return 0;
}
