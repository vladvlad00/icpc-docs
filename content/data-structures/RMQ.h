/**
 * Author: Cristi
 * Description: wtf
 */
struct RMQ {
	vector<vector<int>> rmq;

	void build(const vector<int> &vec) {
		rmq.push_back(vec);

		for(int i = 1; (1 << i) <= vec.size(); ++i) {
			rmq.push_back(vector<int>(vec.size()));
			for(int j = 0; j + (1 << i) - 1 < vec.size(); ++j)
				rmq[i][j] = gcd(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
		}
	}

	int query(int l, int r) {
		int d = 31 - __builtin_clz(r - l + 1);
		return gcd(rmq[d][l], rmq[d][r - (1 << d) + 1]);
	}
};


