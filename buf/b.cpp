#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 110
typedef struct NODE Node;
struct NODE
{
    long long int w;
    int child[N];
    int n;
};
long long int target;
Node nodes[N];
typedef struct VECTOR Vector; 
struct VECTOR 
{
	int v[N]; 
};
Vector path;
Vector vec[N];
int cv;
int cmp(const void *p, const void *q) {
	Vector pp = *(Vector *)p;
	Vector qq = *(Vector *)q;
	int cp = *pp.v;
	int cq = *qq.v;
	int sze = cp > cq ? cp : cq;
	for (int i = 1; i <= sze; ++i) {
		if (pp.v[i] < qq.v[i])
			return 1;
		else if (pp.v[i] > qq.v[i]) 
			return -1;
	}
	return -1;
}

void dfs(int index, int nodeNum, long long int sum)
{
    int i, cur;
    if (sum > target)
        return;
    if (sum == target)
    {
        if (nodes[index].n) // 如果有子节点
            return;
		vec[cv++] = path;
        return;
    }
    for (i = 0; i < nodes[index].n; i++)
    {
        cur = nodes[index].child[i];
		path.v[++*path.v] = nodes[cur].w;
        dfs(cur, nodeNum + 1, sum + nodes[cur].w); 
		path.v[*path.v] = -1;
		--*path.v;
	}
}

int main()
{
    int n, m, node, k;
    scanf("%d %d %lld", &n, &m, &target);
    int i, j, p, q;
    for (i = 0; i < n; i++)
        scanf("%lld", &nodes[i].w);
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &node, &k);
        nodes[node].n = k;
        for (j = 0; j < k; j++)
            scanf("%d", &nodes[node].child[j]); 	
	}
	memset(path.v, -1, sizeof path.v);
	*path.v = 0;
	cv = 0;
	path.v[++*path.v] = nodes[0].w;
    dfs(0, 1, nodes[0].w);
	qsort(vec, cv, sizeof(vec[0]), cmp);
	for (int i = 0; i < cv; ++i)
		for (int j = 1; j <= *vec[i].v; ++j)
			printf("%d%c", vec[i].v[j], " \n"[j == *vec[i].v]);
	return 0;
}
