#include <bits/stdc++.h>
using namespace std;

#define N 210
set<string> se;
int n;
char s[N], t[N];

int minRep(char *s) {
    int len = strlen(s);
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = s[(i + k) % len] - s[(j + k) % len];
        if (!t)
            ++k;
        else {
            if (t > 0)
                i += k + 1;
            else if (t < 0)
                j += k + 1;
            if (i == j)
                j = i + 1;
            k = 0;
        }
        printf("%d %d %d\n", i, j, k);
    }
    return min(i, j);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        se.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            strcpy(t, s);
            strcat(s, t);
            int k = minRep(s);
            s[k + strlen(s) / 2] = 0;
            cout << k << endl;
            se.insert(s + k);
        }
        printf("%d\n", (int)se.size());
    }
    return 0;
}
