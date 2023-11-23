/**
 * Author: Cristi
 * Description: wtf
 */
struct ST {
	int n;
	vector<int> st, lazy;

	ST(int n) : n(n), st(4 * n), lazy(4 * n) {}

	void push(int node) {
		st[2 * node] += lazy[node];
		lazy[2 * node] += lazy[node];
		st[2 * node + 1] += lazy[node];
		lazy[2 * node + 1] += lazy[node];
		lazy[node] = 0;
	}

	void update(int node, int l, int r, int a, int b, int val) {
		if(a <= l && r <= b) { st[node] += val; lazy[node] += val; return; }
		push(node);
		
		int mid = (l + r) / 2;
		if(a <= mid) update(2 * node, l, mid, a, b, val);
		if(mid + 1 <= b) update(2 * node + 1, mid + 1, r, a, b, val);
		
		st[node] = min(st[2 * node], st[2 * node + 1]);
	}

	int query(int node, int l, int r, int a, int b) {
		if(a <= l && r <= b) return st[node];
		push(node);
		
		int mid = (l + r) / 2;
		int v1 = (a <= mid ? query(2 * node, l, mid, a, b) : INF);
		int v2 = (mid + 1 <= b ? query(2 * node + 1, mid + 1, r, a, b) : INF);
		return min(v1, v2);
	}

	void update(int a, int b, int val) { update(1, 1, n, a, b, val); }
	int query(int a, int b) { return query(1, 1, n, a, b); }
};


