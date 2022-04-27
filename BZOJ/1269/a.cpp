#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int N = 2e6 + 10;
rope<char> A, B, T;
int n, pos, len;
char s[N], revs[N];

int main() {
    int _T;
    scanf("%d", &_T);
    char op[5];
    pos = 0;
    while (_T--) {
        scanf("%s", op);
        if (op[0] == 'M') {
            scanf("%d", &pos);
        } else if (op[0] == 'I') {
            scanf("%d", &n);
            for (int i = 0; i < n; ++i) {
                do {
                    s[i] = getchar();
                } while (s[i] == '\n');
                revs[n - i - 1] = s[i];
            }
            s[n] = revs[n] = 0;
            len = A.length();
            A.insert(pos, s);
            B.insert(len - pos, revs);
        } else if (op[0] == 'D') {
            scanf("%d", &n);
            len = A.length();
            A.erase(pos, n);
            B.erase(len - pos - n, n);
        } else if (op[0] == 'R') {
            scanf("%d", &n);
            len = A.length();
            T = A.substr(pos, n);
            A = A.substr(0, pos) + B.substr(len - pos - n, n) + A.substr(pos + n, len - pos - n);
            B = B.substr(0, len - pos - n) + T + B.substr(len - pos, pos);
        } else if (op[0] == 'G') {
            printf("%c\n", A[pos]);
        } else if (op[0] == 'P') {
            --pos;
        } else if (op[0] == 'N') {
            ++pos;
        }
    }
    return 0;
}
