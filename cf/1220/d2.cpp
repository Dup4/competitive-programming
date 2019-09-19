    #include<bits/stdc++.h>
    using namespace std;
    long long d[200000];
    int main() {
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%lld", &d[i]);
        int ma_cnt = 0;
        long long target = 0;
        for(long long i = 1; i <= 1e18; i <<= 1) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                if(d[j] % i == 0 && d[j] / i % 2 == 1) {
                    cnt++;
                }
            }
            if(cnt > ma_cnt) {
                ma_cnt = cnt;
                target = i;
            }
        }
        printf("%d\n", n - ma_cnt);
        for(int i = 0; i < n; i++) {
            if(d[i] % target != 0 || d[i] / target % 2 == 0) printf("%lld ",d[i]);
        }
        return 0;
    }
