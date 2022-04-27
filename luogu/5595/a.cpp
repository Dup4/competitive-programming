#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N], A[N], B[N];
int n;

void gao() {
    int equal = 1;
    for (int i = n; i >= 1; --i) {
        if (s[i] == 'Z' && equal == 0) {
            puts("-1");
            return;
        }
        if (s[i] != 'Z')
            equal = 0;
    }
    for (int i = n; i >= 1; --i) {
        if (s[i] == 'Z')
            A[i] = '0', B[i] = '0';
        else if (s[i] == 'X')
            A[i] = '1', B[i] = '0';
        else
            A[i] = '0', B[i] = '1';
    }
    A[n + 1] = B[n + 1] = 0;
    printf("%s\n%s\n", A + 1, B + 1);
}

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        gao();
    }
    return 0;
}
