#include <cstdio>
#include <cmath>
#include <cstdint>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>
#include <tuple>

using std::tuple;
using std::make_pair;
using std::vector;
using std::sort;
using std::sort;
using std::pair;
using std::get;

const int maxn=1e5+100;

int blo[maxn],a[maxn];

struct Qry
{
    int l,r,id;
    int64_t ans;
    inline bool operator< (const Qry& q){return blo[l]==blo[q.l]?r<q.r:l<q.l;}
}Q[maxn];

vector<tuple<int,int,int>> v[maxn];

int main()
{
    // freopen("data.in","r",stdin);
    // freopen("my.out","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    if (k>14)
    {
        for (int i=1;i<=m;++i) puts("0");
        return 0;
    }
    for (int i=1;i<=n;++i)
        scanf("%d",a+i);
    for (int i=1;i<=m;++i)
        scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    vector<int> buc;
    for (int i=0;i<16384;++i)
        if (__builtin_popcount(i)==k) buc.push_back(i);
    // for (auto x:buc)
    //     fprintf(stderr,"%d ",x);
    int T=sqrt(n);
    for (int i=1;i<=n;++i) blo[i]=(i-1)/T+1;
    sort(Q+1,Q+m+1);

     /***************/
     /*  L右移：l正r负 *\
     /*  l左移：l负r正 *\
     /*  r右移：r正l负 *\
     /*  r左移：r负l正 *\
     /***************/
    static int t[maxn];
    static int pref[maxn];
    for (int i=1;i<=n;++i)
    {
        for (auto x:buc) ++t[a[i]^x];
        pref[i]=t[a[i+1]];
    }
    memset(t,0,sizeof(t));
    // 预处理前缀贡献
    for (int i=1,L=1,R=0;i<=m;++i)
    {
        int l=Q[i].l,r=Q[i].r;
        if (L<l) v[R].emplace_back(L,l-1,-i);
        while (L<l) {Q[i].ans+=pref[L-1];++L;} 
        if (L>l) v[R].emplace_back(l,L-1,i);
        while (L>l) {Q[i].ans-=pref[L-2];--L;}
        if (R<r) v[L-1].emplace_back(R+1,r,-i);
        while (R<r) {Q[i].ans+=pref[R];++R;}
        if (R>r) v[L-1].emplace_back(r+1,R,i);
        while (R>r) {Q[i].ans-=pref[R-1];--R;}
    }
    //模拟莫队，算出来第一类贡献，对第二类贡献打上标记
    static int64_t ans[maxn];
    for (int i=1,id,l,r;i<=n;++i)
    {
        for (auto x:buc) ++t[a[i]^x];
        for (const auto& x:v[i])
        {
            std::tie(l,r,id)=x;
            // if (i>=l) fprintf(stderr,"%d %d\n",i,l);
            for (int j=l,tmp=0;j<=r;++j)
            {
                tmp=t[a[j]];
                if (j<=i && k==0) --tmp;// 这里（按我的蒟蒻写法）k==0的时候需要特判，因为x^x永远是0，但自己对自己不能产生贡献。
                if (id<0) Q[-id].ans-=tmp;
                else Q[id].ans+=tmp;
            }
        }
    }
    for (int i=1;i<=m;++i) Q[i].ans+=Q[i-1].ans;
    for (int i=1;i<=m;++i) ans[Q[i].id]=Q[i].ans;
    for (int i=1;i<=m;++i) printf("%lld\n",ans[i]);
}
