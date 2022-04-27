#include <bits/stdc++.h>
using namespace std;

#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 2e6 + 10;
char s[N], t[N], tt[N];
int n;
struct ExKMP {
    int Next[N];
    int extend[N];
    //下标从1开始
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

void run() {
    int m = 0;
    cin >> (s + 1);
    m = strlen(s + 1);
    for (int i = 2; i <= n; ++i) {
        cin >> (t + 1);
        int lent = strlen(t + 1);
        tt[0] = 0;
        if (m < lent) {
            for (int j = 1; j <= m; ++j) {
                tt[j] = s[j];
            }
            tt[m + 1] = '\0';
        } else {
            for (int j = m - lent + 1, i = 1; j <= m; ++j, ++i) {
                tt[i] = s[j];
                //	cout << s[j] << " " << tt[j] << endl;
            }
            tt[lent + 1] = '\0';
        }
        //	cout << i << " " << (tt + 1) << endl;
        exkmp.work(tt, t);
        int Max = 0;
        //		cout << (tt + 1) << " " << (t + 1) << endl;
        int lim = min(m, lent);
        for (int j = 1; j <= lim; ++j) {
            if (exkmp.extend[j] == lim - j + 1) {
                Max = max(Max, exkmp.extend[j]);
            }
            //			cout << j << " " << exkmp.extend[j] << endl;
        }
        for (int j = Max + 1; j <= lent; ++j) {
            s[++m] = t[j];
        }
        s[m + 1] = '\0';
        //	cout << (s + 1) << endl;
    }
    cout << (s + 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n) run();
    return 0;
}
