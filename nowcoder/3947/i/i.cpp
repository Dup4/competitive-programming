#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, mod = 20010905;
int n, f[20];
char s[N];
inline void chadd(int &x, int y) {
    x += y;
    while (x >= mod) x -= mod;
    while (x < 0) x += mod;
}

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] -= 'A';
                s[i] += 'a';
            }
            if (s[i] == 'i') {
                chadd(f[1], 1);
            } else if (s[i] == 'l') {
                chadd(f[2], f[1]);
            } else if (s[i] == 'o') {
                chadd(f[3], f[2]);
                chadd(f[7], f[6]);
            } else if (s[i] == 'v') {
                chadd(f[4], f[3]);
            } else if (s[i] == 'e') {
                chadd(f[5], f[4]);
            } else if (s[i] == 'y') {
                chadd(f[6], f[5]);
            } else if (s[i] == 'u') {
                chadd(f[8], f[7]);
            }
        }
        cout << f[8] << endl;
    }
    return 0;
}
