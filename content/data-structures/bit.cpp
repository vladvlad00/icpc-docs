/**
 * Author: Cristi
 * Description: wtf
 */

template<class T = int>
struct BIT {
	vector<T> bit;

	BIT(int n) : bit(n + 1, 0) {}

	void update(int p, T val) {
		for(; p < bit.size(); p += p & (-p)) bit[p] += val;
	}

	T query(int p) {
		T res;
		for(res = 0; p; p &= p - 1) res += bit[p];
		return res;
	}

	T query(int l, int r) {
		return query(bit, r) - query(bit, l - 1);
	}
};

