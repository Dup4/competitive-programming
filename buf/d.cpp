#include <bits/stdc++.h>
#define N 251000
typedef struct EDGE Edge;
struct EDGE
{
    int b, e, c;
};
Edge new_edge(int b, int e, int c)
{
    Edge edge;
    edge.b = b;
    edge.e = e;
    edge.c = c;
    return edge;
}
/*int less(const void * a, const void * b)
{
    return (*(EDGE *)a).c < (*(EDGE *)b).c ? 1 : -1;
}*/
// int cmp (const void * a, const void * b)
// {
//   return ( *(int*)a - *(int*)b );
//}

int cmp(const void *q, const void *p) {
	struct EDGE pp = *(struct EDGE *)p;
	struct EDGE qq = *(struct EDGE *)q;
	if (pp.c < qq.c) return 1;
	return -1;
}

Edge es[N];
int ans[N], root[N];
int tot1 = 0, tot2 = 0;
int b, e, c, f, n, m, worstv;

int findroot(int x)
{
    if (root[x] != x)
        return root[x] = findroot(root[x]);
    return root[x];
}

int getcost(int k)
{
    int linkcount = 0, cost = 0;
    for (int i = 1; i <= n; i++)
    {
        root[i] = i;
    }
    for (int i = 0; i < tot1; i++)
    {
        Edge item = es[i];

        if (item.b == k || item.e == k)
            continue;
        int rb = findroot(item.b);
        int re = findroot(item.e);
        if (rb != re)
        {
            cost += item.c;
            root[rb] = re;
            linkcount++;
            if (linkcount == n - 2)
                return cost;
        }
    }
    return 9999999;
}
int main()
{
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d%d%d%d", &b, &e, &c, &f);
        if (f == 1)
            c = 0;
        es[tot1++] = new_edge(b, e, c);
    }
    qsort(es,m,sizeof(es[0]),cmp); 
    /*for (i = 0; i < m; i++)
    {
        for (j = 0; j < m - 1; j++)
        {
            if (less(es[j + 1], es[j]))
            {
                Edge tmp = es[j];
                es[j] = es[j + 1];
                es[j + 1] = tmp;
            }
        }
    }*/
    for (i = 1; i <= n; i++)
    {
        int v = getcost(i);
        if (v > worstv)
        {
            worstv = v;
            tot2 = 0;
            ans[tot2++] = i;
        }
        else if (v == worstv)
            ans[tot2++] = i;
    }
    if (worstv == 0)
        printf("0\n");
    else
    {
        for (int i = 0; i < tot2; i++)
        {
            printf("%d", ans[i]);
            if (i == tot2 - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
    return 0;
}
