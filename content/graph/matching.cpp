/**
 * Author: Cristi
 * Description: wtf
 */
struct Matching {
	int m, n;
	vector<int> l, r;
	vector<bool> vis, ok, coverL, coverR;
	vector<vector<int>> adj, adjt;

	Matching(int m, int n) : m(m), n(n), l(n), r(m), vis(m), ok(m), adj(m), adjt(n), coverL(m), coverR(n) {}
	
	bool pairUp(int v) {
		if(vis[v]) return false;
		vis[v] = true;

		for(auto u : adj[v])
			if(l[u] == -1) return l[u] = v, r[v] = u, true;
		
		for(auto u : adj[v])
			if(pairUp(l[u])) return l[u] = v, r[v] = u, true;

		return false;
	}

	void bfs(vector<vector<int>> adj, vector<int> l, vector<int> r) {
		queue<int> q;
		vis.assign(r.size(), false);
		for(int i = 0; i < r.size(); ++i) if(r[i] == -1) q.push(i), vis[i] = true;
		for(; !q.empty(); q.pop()) {
			int v = q.front();
			ok[v] = true;
			for(auto u : adj[v])
				if(!vis[l[u]]) q.push(l[u]), vis[l[u]] = true;
		}
	}

	void cover(int v) {
		for(auto u : adj[v])
			if(!coverR[u]) {
				coverR[u] = true;
				coverL[l[u]] = false;
				cover(l[u]);
			}
	}

	void addEdge(int a, int b) {
		adj[a].push_back(b);
		adjt[b].push_back(a);
	}

	int matching() {
		int sz;
		bool changed;

		l.assign(n, -1);
		r.assign(m, -1);
		for(sz = 0, changed = true; changed; ) {
			vis.assign(m, false);
			changed = false;
			for(int i = 0; i < m; ++i)
				if(r[i] == -1 && pairUp(i)) ++sz, changed = true;
		}
		return sz;
	}

	// if ok[i] == false => i belongs to all maximum matchings
	void computeVerticesBelongingToAllmaximumMatchings() {
		bfs(adj, l, r);
		bfs(adjt, r, l);
	}

	void computeMinimumVertexCover() {
		for(int i = 0; i < m; ++i) if(r[i] != -1) coverL[i] = true;
		for(int i = 0; i < m; ++i) if(r[i] == -1) cover(i);
	}
};

