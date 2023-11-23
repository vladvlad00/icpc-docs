/**
 * Author: Cristi
 * Description: wtf
 */
 struct SegTree {
	int n;
	vector<int> st;
	
	SegTree(int n) : n(n), st(2 * n) {}

	void update(int p, int val) {
		for(st[p += n] = val; p > 1; p >>= 1) st[p >> 1] = max(st[p], st[p ^ 1]);
	}

	int query(int l, int r) {
		int res = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l & 1) res = max(res, st[l++]);
			if(r & 1) res = max(res, st[--r]);
		}
		return res;
	}
};


