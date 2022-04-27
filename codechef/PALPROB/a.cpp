#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
#define ALP 26
int n;
char s[N];
int f[N];
struct PAM {
    //每个节点代表一个本质不同的回文串
    struct node {
        int Next[ALP];
        int fail;
        int half;
        int len, num, cnt;
        node(int _len = 0) {
            memset(Next, 0, sizeof Next);
            fail = 0;
            half = 0;
            num = 0;
            cnt = 0;
            len = _len;
        }
    } t[N];
    //存放添加的字符
    int s[N];  // 存放添加的字符
               //指向添加最后一个字符后的节点
    int last;
    //已添加字符个数
    int n;
    //节点个数
    int p;

    int newnode(int len) {  // 初始化节点，w=长度
        t[p] = node(len);
        return p++;
    }
    // 0为长度为偶数的回文子串的根节点
    // 1为长度为奇数的回文子串的根节点
    //最后节点总数是p，但是节点标号是[0, p - 1]
    void init() {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1;  // 开头放一个字符集中没有的字符，减少特判
        t[0].fail = 1;
    }
    int get_fail(int x) {  // 和KMP一样，失配后找一个尽量最长的
        while (s[n - t[x].len - 1] != s[n]) x = t[x].fail;
        return x;
    }
    bool add(int c) {
        bool F = 0;
        //设置偏移量
        c -= 'a';
        s[++n] = c;
        //通过上一个回文串找这个回文串的匹配位置
        int cur = get_fail(last);
        //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
        if (!t[cur].Next[c]) {
            int now = newnode(t[cur].len + 2);  //新建节点
                                                //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;
            if (t[now].len == 1) {
                t[now].half = 0;
            } else {
                int pos = t[cur].half;
                while (s[n - t[pos].len - 1] != s[n] || t[t[pos].Next[c]].len > t[now].len / 2) pos = t[pos].fail;
                t[now].half = t[pos].Next[c];
            }
            t[now].num = 1 + (t[now].len / 2 == t[t[now].half].len ? t[t[now].half].num : 0);
            F = 1;
        }
        last = t[cur].Next[c];
        ++t[last].cnt;
        //返回的当前字符加入后是否新增了一个本质不同的回文串
        return F;
        //那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
    void count() {
        // 最后统计一遍每个节点出现个数
        // 父亲累加儿子的cnt,类似SAM中parent树
        // 满足parent拓扑关系
        for (int i = p - 1; i >= 0; --i) {
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
} pam;

int main() {
    f[1] = 1;
    for (int i = 2; i <= 100000; ++i) f[i] = 1 + f[i / 2];
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        pam.init();
        for (int i = 1; i <= n; ++i) {
            pam.add(s[i]);
        }
        pam.count();
        ll res = 0;
        for (int i = 0; i <= pam.p - 1; ++i) {
            res += 1ll * pam.t[i].num * pam.t[i].cnt;
        }
        printf("%lld\n", res);
    }
    return 0;
}
