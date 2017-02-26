# include <bits/stdc++.h>
# define eps 1e-6
# define LL long long
# define pii pair<int, int>
# define pb push_back
# define mp make_pair
using namespace std;
const int MAXN = 100010;
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
