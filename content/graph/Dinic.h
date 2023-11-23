/**
 * Author: Cristi
 * Description: wtf
 */
struct NetworkFlow {
	const int INT_INF = 0x3f3f3f3f;
	const ll LL_INF = 1e18;

	struct Edge {
		int to, flow;
	};

	int n, source, sink;
	vector<int> dst, ptr;
	vector<Edge> edges;
	vector<vector<int>> adj;

	NetworkFlow(int n) : n(n) {
		source = 0;
		sink = n - 1;

		dst.resize(n);
		adj.resize(n);
	}

	void addEdge(int a, int b, int cap) {
		adj[a].push_back(edges.size());
		edges.push_back({b, cap});

		adj[b].push_back(edges.size());
		edges.push_back({a, 0});
	}

	bool bfs(int v) {
		dst.assign(n, INT_INF);

		queue<int> q;
		for(dst[v] = 0, q.push(v); !q.empty(); q.pop()) {
			v = q.front();

			for(auto id : adj[v])
				if(dst[edges[id].to] > 1 + dst[v] && edges[id].flow) {
					dst[edges[id].to] = 1 + dst[v];
					q.push(edges[id].to);
				}
		}

		return dst[sink] != INT_INF;
	}

	ll dfs(int v, ll flow) {
		if(v == sink || !flow) return flow;

		for(; ptr[v] < adj[v].size(); ++ptr[v]) {
			int id = adj[v][ptr[v]];
			int u = edges[id].to;
			if(edges[id].flow && dst[u] == 1 + dst[v]) {
				int pushed = dfs(u, min(flow, (ll) edges[id].flow));
				if(pushed) {
					edges[id].flow -= pushed;
					edges[id ^ 1].flow += pushed;
					return pushed;
				}
			}
		}

		return 0;
	}

	ll dinic() {
		ll flow, total;

		for(total = 0; bfs(source); ) {
			ptr.assign(n, 0);
			while(flow = dfs(source, LL_INF)) total += flow;
		}

		return total;
	}

	void clear() {
		edges.clear();
		for(int i = 0; i < n; ++i) adj[i].clear();
	}
};

