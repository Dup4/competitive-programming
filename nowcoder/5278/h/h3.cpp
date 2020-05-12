#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

#define dbg(x...)             \
    do {                      \
        cout << #x << " -> "; \
        err(x);               \
    } while (0)

void err() {
    cout << endl;
}

template <class T, class... Ts>
void err(const T& arg, const Ts&... args) {
    cout << arg << ' ';
    err(args...);
}

int n, k, sum;
char s[N];
int cnt[20];
vector<int> vec;

bool ok() {
    for (int i = k - 1; i >= 0; --i) {
        int it = vec[i];
        for (int j = 9; j >= 0; --j) {
            if (!cnt[j])
                continue;
            if ((sum - it + j) % 3 == 0) {
                vec[i] = j;
                return true;
            }
        }
    }
    return false;
}

void gao() {
    for (int i = k - 1; i >= 0; --i) {
        int it = vec[i];
        for (int j = 9; j >= 0; --j) {
            if (!cnt[j])
                continue;
            int a = (it % 3 + 2) % 3;
            if (j % 3 == a) {
                vec[i] = j;
                sum = sum - it + j;
                cnt[j]--;
                cnt[it]++;
                return;
            }
        }
    }
}

int main() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        memset(cnt, 0, sizeof cnt);
        sum = 0;
        vec.clear();
        scanf("%s %d", s + 1, &k);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) {
            cnt[s[i] - '0']++;
        }
        int need = k;
        for (int i = 9; i >= 0; --i) {
            while (need > 0 && cnt[i]) {
                vec.push_back(i);
                need--;
                cnt[i]--;
                sum += i;
            }
        }
        if (sum % 3 != 0) {
            if (!ok()) {
                gao();
                gao();
                if (sum % 3 != 0) {
                    puts("-1");
                    continue;
                }
            }
        }
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        if (vec[0] == 0 && vec.size() > 1) {
            puts("-1");
            continue;
        }
        for (auto it : vec) {
            printf("%d", it);
        }
        puts("");
    }
    return 0;
}
