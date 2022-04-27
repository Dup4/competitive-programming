#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 510010
#define ALP 26

struct Manacher {
    int len;
    char Ma[N << 1];
    int Mp[N << 1];
    void init(int len) {
        this->len = len;
    }
    void work(char *s) {
        int l = 0;
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
    }
    bool check(int l, int r) {
        int il = (l + 1) * 2, ir = (r + 1) * 2;
        int mid = (il + ir) / 2;
        int len = (r - l + 2) / 2;
        return (Mp[mid] / 2) >= len;
    }
} man;

struct PAM {
    int Next[N][ALP];
    int fail[N];
    int cnt[N];
    int num[N];
    int len[N];
    int s[N];
    int last;
    int n;
    int p;

    int newnode(int w) {  // 初始化节点，w=长度
        for (int i = 0; i < ALP; i++) Next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }
    void init() {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1;
        fail[0] = 1;
    }
    int get_fail(int x) {
        while (s[n - len[x] - 1] != s[n]) x = fail[x];
        return x;
    }
    bool add(int c) {
        bool F = 0;
        c -= 'a';
        s[++n] = c;
        int cur = get_fail(last);
        if (!Next[cur][c]) {
            int now = newnode(len[cur] + 2);
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
            F = 1;
        }
        last = Next[cur][c];
        cnt[last]++;
        return F;
    }
    void count() {
        for (int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
    }
} pam;
char s[N];
int f[N], g[N];
int res[N], len;

int main() {
    while (scanf("%d", &len) != EOF) {
        scanf("%s", s);
        man.init(len);
        man.work(s);
        pam.init();
        for (int i = 0; i <= len; ++i) res[i] = 0;
        for (int i = 0; i < len; ++i) {
            if (pam.add(s[i])) {
                g[i] = 1;
            } else {
                g[i] = 0;
            }
            f[i] = pam.last;
        }
        pam.count();
        for (int i = 0; i < len; ++i) {
            if (g[i] == 0)
                continue;
            int Len = pam.len[f[i]];
            if (Len % 4)
                continue;
            int l = i - Len + 1;
            int r = i;
            int mid = (l + r) >> 1;
            if (man.check(l, mid)) {
                res[Len] += pam.cnt[f[i]];
            }
        }
        int Max = 0;
        for (int i = len; i >= 1; --i)
            if (res[i]) {
                Max = i;
                break;
            }
        printf("%d\n", Max);
    }
    return 0;
}
