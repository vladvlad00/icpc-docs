/**
 * Author: Cristi
 * Description: wtf
 */

int comp[N];
bool vis[N];
vector<int> adj[N], adjt[N], ord;

void dfs(int v) {
	vis[v] = true;
	for(auto u : adj[v])
		if(!vis[u]) dfs(u);
	ord.push_back(v);
}

void dfst(int v, int nrc) {
	vis[v] = true;
	comp[v] = nrc;
	for(auto u : adjt[v])
		if(!vis[u]) dfst(u, nrc);
}


for(int i = 1; i <= n; ++i)
	if(!vis[i]) dfs(i);

reverse(all(ord));
memset(vis, 0, sizeof vis);

int nrc = 0;
for(auto i : ord) if(!vis[i]) dfst(i, ++nrc);

