/**
 * Author: Cristi
 * Description: wtf
 */
struct HLD {
	int n, t;
	vector<int> in, out, head, fth, h, sz;
	vector<vector<int>> adj;
	SegTree segTree;
	// in[i] = time entering node i
	// out[i] = time leaving node i
	// head[i] = head of path containing node i
	// fth[i] = parent of node i in original tree
	// h[i] = height of node i in original tree starting from 0
	// sz[i] = size of subtree of i in original tree

	HLD(int n) : n(n), in(n), out(n), head(n), fth(n), h(n), sz(n), adj(n), segTree(n) {}

	void addEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void dfsSize(int v, int p = -1) {
		sz[v] = 1;
		for(auto &u : adj[v])
			if(u != p) {
				fth[u] = v;
				h[u] = 1 + h[v];
				dfsSize(u, v);
				sz[v] += sz[u];
				if(sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
			}
	}

	void dfsHld(int v, int p = -1) {
		in[v] = t++;
		for(auto u : adj[v])
			if(u != p) {
				head[u] = (u == adj[v][0] ? head[v] : u);
				dfsHld(u, v);
			}
		out[v] = t;
	}

	void build(const vector<int> &v) {
		t = 0;
		sz.assign(n, 0);

		dfsSize(0);
		dfsHld(0);
	
		for(int i = 0; i < n; ++i) segTree.update(in[i], v[i]);
	}

	void update(int v, int val) {
		segTree.update(in[v], val);
	}

	int query(int v, int u) {
		int res = 0;
		while(head[v] != head[u]) {
			if(h[head[v]] > h[head[u]]) swap(v, u);

			res = max(res, segTree.query(in[head[u]], in[u] + 1));
			u = fth[head[u]];
		}

		if(h[v] > h[u]) swap(v, u);
		res = max(res, segTree.query(in[v], in[u] + 1));

		return res;
	}

	// subtree of v: [in_v, out_v)
	// path from v to the heavy path head: [in_head_v, in_v]
};


