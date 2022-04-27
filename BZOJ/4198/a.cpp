#include <bits/stdc++.h>
using namespace std;

/*
        BZOJ 4198
        有一篇文章，里面由n种单词组成
    将n种单词用k进制串s_i来替换第i种单词
        第i种单词出现的频率为w_i
        满足：
        对于任意的1 <= i, j <= n, i != j有s_i != s_j
        如何选择s_i,使得替换以后文章的总长度最小
        并且在总长度最小的情况下，使得最长的s_i长度最小
        输出最小的总长度和最长的s_i的长度

        k叉哈夫曼树 考虑最后一次合并的时候不够k个
        可以提前补一些权为0的叶子节点进去
*/

#define ll long long
#define N 100010
#define pli pair<ll, int>
#define fi first
#define se second
int n, k;
ll a[N];

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", a + i);
        }
        priority_queue<pli, vector<pli>, greater<pli> > pq;
        for (int i = 1; i <= n; ++i) {
            pq.push(pli(a[i], 0));
        }
        //提前补权为0的叶子节点
        while ((n - 1) % (k - 1)) {
            pq.push(pli(0, 0));
            ++n;
        }
        ll res = 0;
        while ((int)pq.size() >= k) {
            pli u = pli(0, 0), v;
            for (int i = 1; i <= k; ++i) {
                v = pq.top();
                pq.pop();
                u.fi += v.fi;
                u.se = max(u.se, v.se + 1);
            }
            res += u.fi;
            pq.push(u);
        }
        printf("%lld\n%d\n", res, pq.top().se);
    }
    return 0;
}
