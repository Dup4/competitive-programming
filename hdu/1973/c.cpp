#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define maxn 100002
using namespace std;
int vis[maxn];
int t;
int b, a, bb[5];
bool sushu(int x) {
    for (int i = 2; i < x; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}
struct node {
    int aa[5];
    int step;
} now, Next;

int f(node it) {
    int res = 0;
    for (int i = 3; i >= 0; --i) res = res * 10 + it.aa[i];
    return res;
}

int bfs(int step) {
    now.step = step;
    queue<node> q;
    q.push(now);
    vis[a] = 1;
    while (!q.empty()) {
        now = q.front();
        q.pop();
        // cout << f(now) << endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j <= 9; j++) {
                Next = now;
                //	Next.aa[0]=now.aa[0];
                //	Next.aa[1]=now.aa[1];
                //	Next.aa[2]=now.aa[2];
                //	Next.aa[3]=now.aa[3];
                Next.aa[i] = j;
                if (Next.aa[0] == bb[0] && Next.aa[1] == bb[1] && Next.aa[2] == bb[2] && Next.aa[3] == bb[3])
                    return Next.step + 1;
                if (Next.aa[i] == now.aa[i] || Next.aa[3] == 0)
                    continue;
                int num = Next.aa[3] * 1000 + Next.aa[2] * 100 + Next.aa[1] * 10 + Next.aa[0];
                if (vis[num] == 0 && sushu(num)) {
                    vis[num] = 1;
                    Next.step++;
                    q.push(Next);
                }
            }
        }
    }
    // return 1e9;
}
int main(void) {
    cin >> t;
    while (t--) {
        memset(vis, 0, sizeof(vis));
        scanf("%d%d", &a, &b);
        now.aa[0] = a % 10;
        now.aa[1] = a / 10 % 10;
        now.aa[2] = a / 100 % 10;
        now.aa[3] = a / 1000;
        bb[0] = b % 10;
        bb[1] = b / 10 % 10;
        bb[2] = b / 100 % 10;
        bb[3] = b / 1000;
        if (a == b)
            printf("0\n");
        else {
            int count = bfs(0);
            printf("%d\n", count);
        }
    }
}
