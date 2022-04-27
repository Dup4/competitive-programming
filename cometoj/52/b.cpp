#include <bits/stdc++.h>
using namespace std;

int a[4], res;
map<string, int> used;

bool ok(string s) {
    int pos = -1;
    for (int i = 0; i < 4; ++i) {
        if (s[i] == '1') {
            pos = i;
            break;
        }
    }
    for (int i = 1; i <= 3; ++i) {
        if (s[(pos + i) % 4] != i + 1 + '0') {
            return 0;
        }
    }
    return 1;
}
void DFS(string s, int dep) {
    if ((used.find(s) != used.end() && used[s] <= dep) || dep >= res)
        return;
    used[s] = dep;
    if (ok(s)) {
        res = min(res, dep);
        return;
    }
    swap(s[0], s[1]);
    DFS(s, dep + 1);
    swap(s[0], s[1]);
    swap(s[1], s[2]);
    DFS(s, dep + 1);
    swap(s[1], s[2]);
    swap(s[2], s[3]);
    DFS(s, dep + 1);
    swap(s[2], s[3]);
    swap(s[0], s[3]);
    DFS(s, dep + 1);
    swap(s[0], s[3]);
}

int main() {
    used.clear();
    string s = "";
    for (int i = 0; i < 4; ++i) scanf("%d", a + i), s += a[i] + '0';
    res = 1e9;
    DFS(s, 0);
    printf("%d\n", res);
    return 0;
}
