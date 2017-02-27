/*
	题目：给出一棵树，每个节点都有一个color值，然后让你输出对于这个节点的子树中，出现次数最多的颜色的权值和是多少
	分析：
		对于每个节点不仅要考虑他的儿子，还要考虑孙子，
		所以每个节点又保存子数中的信息，用两个map：一个保存<color, 个数> 另外一个保存<个数，sum>
		启发式合并map，对于每一个子树，我们都维护一个map，然后从小的合并到大的中，均摊下来复杂度不会很高
*/
# include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
typedef long long LL;
int n;
map <int, int> cnt[MAXN]; // <color, 几个>
map <int, LL> sumv[MAXN]; // <个数, sum>
vector <int> G[MAXN];

LL ans[MAXN];
void dfs(int u, int fa)
{
	for(int i = 0; i < G[u].size(); i++)
    {
		int v = G[u][i];
		if (v == fa)
            continue;
		dfs(v, u);
        // 回溯过程
		if(cnt[u].size() < cnt[v].size()) // 交换合并
		{
			swap(cnt[u], cnt[v]);
			swap(sumv[u], sumv[v]);
		}
		map<int, int> :: iterator it;
		for(it = cnt[v].begin(); it != cnt[v].end(); it++)// 儿子的 <颜色值，个数>
        {
            // sum【和儿子颜色相同的个数】  -= 颜色值
			sumv[u][cnt[u][it->first]] -= it->first;
			cnt[u][it->first] += it->second; // 父亲和孩子 相同的颜色的个数相加
			sumv[u][cnt[u][it->first]] += it->first;
		}
	}
	ans[u] = sumv[u].rbegin()->second;
}
int main()
{
	scanf("%d", &n);
	int c, u, v;
	for(int i = 1; i <= n; i++)
    {
		scanf("%d", &c);
		cnt[i][c] = 1;
		sumv[i][1] = c;
	}
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);

	for(int i = 1; i <= n; i++)
		printf("%I64d ", ans[i]);
	return 0;
}
