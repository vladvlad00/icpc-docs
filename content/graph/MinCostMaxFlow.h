/**
 * Author: Cristi
 * Description: wtf
 */
const int INF = 0x3f3f3f3f;

struct MCMF {
	struct Edge {
		int to, flow, cst;
	};

	int n, source, sink;
	vector<int> d, reald, newd, prv;
	vector<bool> vis;
	vector<Edge> edges;
	vector<vector<int>> adj;

	MCMF(int n) : n(n), source(0), sink(n - 1), d(n), reald(n), newd(n), prv(n), vis(n), adj(n) {}

	void addEdge(int a, int b, int cap, int cst) {
		adj[a].push_back(edges.size());
		edges.push_back({b, cap, cst});

		adj[b].push_back(edges.size());
		edges.push_back({a, 0, -cst});
	}

	void bellman() {
		priority_queue<pii> q;
		fill(all(d), INF);

		for(d[source] = 0, q.push({0, source}); !q.empty(); ) {
			int dst = -q.top().fi;
			int v = q.top().se;
			q.pop();

			if(dst != d[v]) continue;

			for(auto id : adj[v]) {
				int u = edges[id].to;
				if(edges[id].flow && d[u] > d[v] + edges[id].cst) {
					d[u] = d[v] + edges[id].cst;
					q.push({-d[u], u});
				}
			}
		}
	}

	bool dijkstra() {
		priority_queue<pii> q;
		fill(all(newd), INF);
		fill(all(vis), false);

		for(reald[source] = newd[source] = 0, q.push({0, source}); !q.empty(); ) {
			int dst = -q.top().fi;
			int v = q.top().se;
			q.pop();

			if(vis[v]) continue;
			vis[v] = true;

			for(auto id : adj[v]) {
				int u = edges[id].to;
				int w = d[v] + edges[id].cst - d[u];
				if(edges[id].flow && newd[u] > newd[v] + w) {
					newd[u] = newd[v] + w;
					reald[u] = reald[v] + edges[id].cst;
					prv[u] = id;
					q.push({-newd[u], u});
				}
			}
		}

		return newd[sink] < INF;
	}

	pii get() {
		int flow, cst;

		bellman();

		for(flow = cst = 0; dijkstra(); ) {
			int pushed = INF;
			for(int v = sink; v != source; v = edges[prv[v] ^ 1].to) {
				pushed = min(pushed, edges[prv[v]].flow);
			}

			flow += pushed;

			for(int v = sink; v != source; v = edges[prv[v] ^ 1].to) {
				cst += pushed * edges[prv[v]].cst;
				edges[prv[v]].flow -= pushed;
				edges[prv[v] ^ 1].flow += pushed;
			}

			d = reald;
		}

		return { flow, cst };
	}
};


