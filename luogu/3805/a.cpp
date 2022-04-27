#include <bits/stdc++.h>
using namespace std;
const int N = 1.1e7 + 5;
char s[N];

struct Manacher {
    int len, l;
    char Ma[N << 1];
    int Mp[N << 1];
    // 0-index
    void work(char *s) {
        len = strlen(s);
        l = 0;
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
    //判断s[l]-s[r]是否是一个回文串
    bool check(int l, int r) {
        int il = (l + 1) * 2, ir = (r + 1) * 2;
        int mid = (il + ir) / 2;
        int len = (r - l + 2) / 2;
        return (Mp[mid] / 2) >= len;
    }
    //找串中最长的回文串长度
    int Max() {
        int res = 0;
        for (int i = 0; i < l; ++i) res = max(res, Mp[i] - 1);
        return res;
    }
} man;

int main() {
    scanf("%s", s);
    man.work(s);
    printf("%d\n", man.Max());
    return 0;
}
