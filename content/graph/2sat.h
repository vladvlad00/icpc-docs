/**
 * Author: Cristi
 * Description: wtf
 */
struct Sat {
	int n;
	vector<int> ord, val, compId;
	vector<bool> vis;
	vector<vector<int>> adj, adjt;

	Sat(int n) : n(2 * n), vis(2 * n), compId(2 * n), adj(2 * n), adjt(2 * n) {}

	void addEdge(int x, int y) {
		x = (x < 0 ? -2 * x - 2 : 2 * x - 1);
		y = (y < 0 ? -2 * y - 2 : 2 * y - 1);
		adj[x].push_back(y);
		adjt[y].push_back(x);
	}

	void addClause(int x, int y) {
		addEdge(-x, y);
		addEdge(-y, x);
	}

	void dfs(int v) {
		vis[v] = true;
		for(auto u : adj[v]) if(!vis[u]) dfs(u);
		ord.push_back(v);
	}

	void dfst(int v, int id) {
		vis[v] = false;
		compId[v] = id;
		if(val[v] == -1) val[v] = 0, val[v ^ 1] = 1;
		for(auto u : adjt[v]) if(vis[u]) dfst(u, id);
	}

	bool solve() {
		val.assign(n, -1);

		for(int i = 0; i < n; ++i) if(!vis[i]) dfs(i);
		for(int nr = 0, i = n - 1; i >= 0; --i) if(vis[ord[i]]) dfst(ord[i], nr++);

		for(int i = 0; i < n; i += 2) if(compId[i] == compId[i + 1]) return false;
		return true;
	}

	int get(int i) {
		return val[2 * i - 1];
	}
};

