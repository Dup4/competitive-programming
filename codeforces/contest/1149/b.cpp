#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, q;
char s[N];
int t[N][30][3];
int id[30][3];
string str[3];
bool vis[N];
int used[N];

bool judge() {
    int pos[3] = {0, 0, 0};
    int now = 0;
    while (1) {
        int Min = 1e9, id = -1;
        for (int i = 0; i < 3; ++i) {
        }
    }
    for (int i = 0, len = s.size(); i < len; ++i) {
        int c = s[i] - 'a';
        bool flag = false;
        for (int j = 0; j < 3; ++j) {
            int tmp = t[pos][c][j];
            if (tmp != n + 1 && !vis[tmp]) {
                pos = tmp;
                used[++used[0]] = pos;
                vis[pos] = 1;
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

void clear() {
    for (int i = 1; i <= used[0]; ++i) {
        vis[used[i]] = 0;
    }
}

bool ok() {
    bool flag = true;
    used[0] = 0;
    for (int i = 0; i < 3; ++i) {
        flag &= judge(str[i]);
        if (!flag) {
            break;
        }
    }
    clear();
    return flag;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        scanf("%s", s + 1);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 3; ++j) {
                id[i][j] = n + 1;
            }
        }
        for (int i = n; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) {
                for (int k = 0; k < 3; ++k) {
                    t[i][j][k] = id[j][k];
                }
            }
            if (i) {
                int pos = s[i] - 'a';
                for (int k = 2; k > 0; --k) {
                    id[pos][k] = id[pos][k - 1];
                }
                id[pos][0] = i;
            }
        }
        for (int i = 0; i < 3; ++i) {
            str[i] = "";
        }
        int pos;
        char op[10], ts[10];
        while (q--) {
            scanf("%s%d", op, &pos);
            switch (op[0]) {
                case '+':
                    scanf("%s", ts);
                    str[pos - 1] += ts[0];
                    break;
                case '-':
                    str[pos - 1].pop_back();
                    break;
                default:
                    assert(0);
            }
            for (int i = 0; i < 3; ++i) {
                cout << str[i] << endl;
            }
            puts(ok() ? "YES" : "NO");
        }
    }
    return 0;
}
