/**
 * Author: Cristi
 * Description: wtf
 */
int fth[N], sz[N];
bool used[N];
vector<pii> adj[N];

void computeSz(int v, int p = -1) {
	sz[v] = 1;
	for(auto [u, w] : adj[v])
		if(u != p && !used[u]) {
			computeSz(u, v);
			fth[u] = v;
			sz[v] += sz[u];
		}
}

int findCentroid(int v, int n, int p = -1) {
	while(true) {
		int heavyCh = -1;
		for(auto [u, w] : adj[v])
			if(u != p && !used[u] && (heavyCh == -1 || sz[u] > sz[heavyCh])) heavyCh = u;

		if(heavyCh == -1 || sz[heavyCh] <= n / 2) return v;
		p = v;
		v = heavyCh;
	}

	return -1;
}

void dfs(int v, int p = -1) {
	// do something with node v

	for(auto [u, w] : adj[v])
		if(u != p && !used[u])
			dfs(u, v);
}

void solve(int v, int n) {
	fth[v] = 0;
	computeSz(v);
	int centroid = findCentroid(v, n);

	dfs(centroid);

	used[centroid] = true;

	for(auto [u, w] : adj[centroid])
		if(!used[u]) solve(u, sz[u]);

	if(fth[centroid] && !used[fth[centroid]]) solve(fth[centroid], n - sz[centroid]);
}
