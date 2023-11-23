/**
 * Author: Cristi
 * Description: wtf
 */
 struct UnionFind {
	vector<int> fth, sz;

	UnionFind(int n) {
		fth.assign(n, -1);
		sz.assign(n, 1);
	}

	int root(int x) { return fth[x] == -1 ? x : fth[x] = root(fth[x]); }

	bool join(int a, int b) {
		a = root(a);
		b = root(b);
		if(a == b) return false;

		if(sz[a] < sz[b]) fth[a] = b, sz[b] += sz[a];
		else fth[b] = a, sz[a] += sz[b];
		return true;
	}
};


