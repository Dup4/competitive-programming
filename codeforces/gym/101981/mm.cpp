#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 1000010
char s[N], t[N];

struct ExKMP {
    int Next[N];
    int extend[N];
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        // Next[1]要特殊考虑
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        // Next[2]初始化
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            //第一种情况
            if (len + i < p + 1)
                Next[i] = len;
            //第二种情况
            else {
                //找到对于子串最靠后已经匹配的位置
                int j = max(p - i + 1, 0);
                //暴力匹配
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }

    void work(char *s, char *t) {
        get_Next(t);
        int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
        while (p <= lent && s[p] == t[p]) ++p;
        p = extend[pos = 1] = p - 1;
        for (int i = 2; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
                p = i + (extend[pos = i] = j) - 1;
            }
        }
    }
} exkmp;

struct Manacher {
    char Ma[N << 1];
    int Mp[N << 1];
    int num[N << 1];
    //字符串从0开始
    void work(char *s) {
        int l = 0, len = strlen(s);
        Ma[l++] = '$';
        Ma[l++] = '#';
        for (int i = 0; i < len; ++i) {
            Ma[l++] = s[i];
            Ma[l++] = '#';
        }
        Ma[l] = 0;
        int mx = 0, id = 0;
        for (int i = 0; i < l; ++i) {
            Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
            while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
            if (i + Mp[i] > mx) {
                mx = i + Mp[i];
                id = i;
            }
        }
        for (int i = 0; i < l; ++i) num[i] = 0;
        for (int i = 2; i < l; ++i) {
            int r = i + Mp[i] - 1;
            ++num[i];
            --num[r + 1];
        }
        for (int i = 2; i < l; ++i) num[i] += num[i - 1];
    }
} man;

int main() {
    while (scanf("%s%s", s + 1, t + 1) != EOF) {
        int lens = strlen(s + 1);
        reverse(s + 1, s + 1 + lens);
        exkmp.work(s, t);
        man.work(s + 1);
        ll res = 0;
        for (int i = 2; i <= lens; ++i) {
            //	printf("%d %d %d\n", i, man.num[2 * (i - 1)], exkmp.extend[i]);
            res += 1ll * (man.num[2 * (i - 1)]) * exkmp.extend[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}
