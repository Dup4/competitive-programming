#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char s[N], t[N];

struct KMP {
    int Next[N], NextVal[N];
    // 0-index
    void get_Next(char *s) {
        int len = strlen(s);
        int i, j;
        j = Next[0] = -1;
        i = 0;
        while (i < len) {
            while (-1 != j && s[i] != s[j]) j = Next[j];
            Next[++i] = ++j;
        }
    }
    void get_NextVal(char *s) {
        int len = strlen(s);
        int i, j;
        j = NextVal[0] = -1;
        i = 0;
        while (i < len) {
            while (j != -1 && s[i] != s[j]) j = NextVal[j];
            NextVal[++i] = ++j;
            if (NextVal[i] >= 0 && s[i] == s[NextVal[i]])
                NextVal[i] = NextVal[NextVal[i]];
        }
    }
    // s是主串 t是模式串
    int work(char *s, char *t) {
        int lens = strlen(s), lent = strlen(t);
        int i, j, ans = 0;
        get_Next(t);
        get_NextVal(t);
        i = j = 0;
        while (i < lens) {
            while (-1 != j && s[i] != t[j]) j = NextVal[j];
            ++i, ++j;
            if (j >= lent) {
                ++ans;
                //输出出现次数
                printf("%d\n", i - lent + 1);
                j = NextVal[j];
            }
        }
        //返回出现次数
        return ans;
    }
} kmp;

int main() {
    while (scanf("%s%s", s, t) != EOF) {
        kmp.work(s, t);
        int lent = strlen(t);
        for (int i = 1; i <= lent; ++i) printf("%d%c", kmp.Next[i], " \n"[i == lent]);
    }
    return 0;
}
