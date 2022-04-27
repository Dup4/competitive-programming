#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200010
#define ALP 26

struct PAM {
    // 每个节点代表一个回文串
    int Next[N][ALP];  // next指针,参照Trie树
    int fail[N];       // fail失配后缀链接
    int cnt[N];        // 此回文串出现个数
    int num[N];        // 以节点i结尾的回文串个数
    int len[N];        // 节点i的回文串长度
    int s[N];          // 存放添加的字符
    int last;          //指向上一个字符所在的节点，方便下一次add
    int n;             // 已添加字符个数
    int p;             // 节点个数

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
        s[n] = -1;  // 开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x) {  // 和KMP一样，失配后找一个尽量最长的
        while (s[n - len[x] - 1] != s[n]) x = fail[x];
        return x;
    }
    void add(int c) {
        c -= 'a';
        s[++n] = c;
        //通过上一个回文串找这个回文串的匹配位置
        int cur = get_fail(last);
        //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
        if (!Next[cur][c]) {
            int now = newnode(len[cur] + 2);  //新建节点
                                              //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = Next[cur][c];
        cnt[last]++;
        //那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
    void count() {
        // 最后统计一遍每个节点出现个数
        // 父亲累加儿子的cnt,类似SAM中parent树
        // 满足parent拓扑关系
        for (int i = p - 1; i >= 0; i--) cnt[fail[i]] += cnt[i];
    }
} pam;
char s[N];
int l[N], r[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        pam.init();
        int len = strlen(s + 1);
        int res = 0;
        for (int i = 1; i <= len; ++i) {
            pam.add(s[i]);
            l[i] = pam.len[pam.last];
        }
        pam.init();
        for (int i = len; i >= 1; --i) {
            pam.add(s[i]);
            r[i] = pam.len[pam.last];
        }
        for (int i = 1; i < len; ++i) res = max(res, l[i] + r[i + 1]);
        printf("%d\n", res);
    }
    return 0;
}
