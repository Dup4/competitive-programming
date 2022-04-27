#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, cnt[15];
struct node {
    char card[20];
    string name;
    int tp, a[4], sum;
    void scan() {
        cin >> name >> card;
        a[0] = a[1] = a[2] = 0;
        memset(cnt, 0, sizeof cnt);
        for (int i = 0, len = strlen(card); i < len; ++i) {
            char c = card[i];
            if (c == 'A')
                ++cnt[1];
            else if (c == 'J')
                ++cnt[11];
            else if (c == 'Q')
                ++cnt[12];
            else if (c == 'K')
                ++cnt[13];
            else if (c == '1')
                ++cnt[10], ++i;
            else
                ++cnt[c - '0'];
        }
        sum = 0;
        for (int i = 1; i <= 13; ++i) sum += i * cnt[i];
        // Royal Straight
        if (cnt[10] == 1 && cnt[11] == 1 && cnt[12] == 1 && cnt[13] == 1 && cnt[1] == 1) {
            tp = 8;
            return;
        }

        // Straight
        for (int i = 5; i <= 13; ++i) {
            bool F = 1;
            for (int j = i - 5 + 1; j <= i; ++j)
                if (cnt[j] == 0) {
                    F = 0;
                    break;
                }
            if (F) {
                tp = 7;
                a[0] = i;
                return;
            }
        }

        // Four of a kind
        for (int i = 1; i <= 13; ++i) {
            if (cnt[i] >= 4) {
                tp = 6;
                a[0] = i;
                a[1] = sum - i * 4;
                return;
            }
        }

        // Full House
        for (int i = 1; i <= 13; ++i) {
            if (cnt[i] == 3) {
                int t = sum - i * 3;
                if (t % 2)
                    break;
                t /= 2;
                if (cnt[t] == 2) {
                    tp = 5;
                    a[0] = i;
                    a[1] = t;
                    return;
                }
                break;
            }
        }

        // Three of a Kind
        for (int i = 1; i <= 13; ++i) {
            if (cnt[i] >= 3) {
                tp = 4;
                a[0] = i;
                a[1] = sum - i * 3;
                return;
            }
        }

        // Two Pairs
        for (int i = 1; i <= 13; ++i) {
            if (cnt[i] == 2) {
                for (int j = i + 1; j <= 13; ++j)
                    if (cnt[j] == 2) {
                        tp = 3;
                        a[0] = j;
                        a[1] = i;
                        a[2] = sum - i * 2 - j * 2;
                        return;
                    }
                break;
            }
        }

        // Pair
        for (int i = 1; i <= 13; ++i) {
            if (cnt[i] == 2) {
                tp = 2;
                a[0] = i;
                a[1] = sum - i * 2;
                return;
            }
        }

        // High Card
        tp = 1;
        a[0] = sum;
    }
    bool operator<(const node &other) const {
        if (tp != other.tp)
            return tp > other.tp;
        for (int i = 0; i < 3; ++i)
            if (a[i] != other.a[i])
                return a[i] > other.a[i];
        return name < other.name;
    }
    void debug() {
        cout << tp << " " << a[0] << " " << a[1] << " " << a[2] << " " << endl;
    }
} a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) a[i].scan();
        sort(a + 1, a + 1 + n);
        //	for (int i = 1; i <= n; ++i) a[i].debug();
        for (int i = 1; i <= n; ++i) cout << a[i].name << "\n";
    }
    return 0;
}
