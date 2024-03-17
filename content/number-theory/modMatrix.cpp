/**
 * Author: cineva
 * Description: ceva
 */

int pw(int base, int exp, int mod) {
	int res;
	for(res = 1; exp; exp >>= 1) {
		if(exp & 1) res = (1LL * res * base) % mod;
		base = (1LL * base * base) % mod;
	}
	
	return res;
}

int modInv(int base, int mod) {
	return pw(base, mod - 2, mod);
}

template<class T = int>
struct ModMatrix {
	int m, n, p;
	vector<vector<T>> a;

	ModMatrix(int m, int n, int p) : m(m), n(n), p(p) {
		for(int i = 0; i < m; ++i)
			a.push_back(vector<T>(n, 0));
	}

	static ModMatrix identity(int n, int p) {
		ModMatrix res(n, n, p);
		for(int i = 0; i < n; ++i) res[i][i] = 1;
		return res;
	}

	vector<T>& operator [](int index) {
		return a[index];
	}

	const vector<T>& operator [](int index) const {
		return a[index];
	}

	friend ModMatrix operator *(const ModMatrix &a, const ModMatrix &b) {
		ModMatrix c(a.m, b.n, a.p);
		mul(a, b, c);

		return c;
	}
	
	friend ModMatrix mul(const ModMatrix &a, const ModMatrix &b, ModMatrix &c) {
		for(int i = 0; i < c.m; ++i)
			for(int j = 0; j < c.n; ++j) {
				c[i][j] = 0;
				for(int k = 0; k < a.n; ++k)
					c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % a.p;
			}

		return c;
	}

	friend ModMatrix pw(ModMatrix base, int exp) {
		ModMatrix res = identity(base.m, base.p), aux(base.m, base.m, base.p);
		for(; exp; exp >>= 1) {
			if(exp & 1) mul(res, base, aux), res.a.swap(aux.a);
			mul(base, base, aux), base.a.swap(aux.a);
		}

		return res;
	}

	friend ModMatrix modInv(ModMatrix a) { // assumes a is invertible
		ModMatrix inv = identity(a.n, a.p);

		for(int i = 0; i < a.m; ++i) {
			int k;
			for(k = i; k < a.m && !a[k][i]; ++k);

			if(i != k) {
				a[i].swap(a[k]);
				inv[i].swap(inv[k]);
			}

			int x = modInv(a[i][i], a.p);
			for(int j = 0; j < a.n; ++j) {
				a[i][j] = (1LL * a[i][j] * x) % a.p;
				inv[i][j] = (1LL * inv[i][j] * x) % a.p;
			}
			
			for(int k = 0; k < a.m; ++k) {
				if(k == i) continue;
				
				int x = a[k][i];
				for(int j = 0; j < a.n; ++j) {
					a[k][j] -= (1LL * a[i][j] * x) % a.p; if(a[k][j] < 0) a[k][j] += a.p;
					inv[k][j] -= (1LL * inv[i][j] * x) % a.p; if(inv[k][j] < 0) inv[k][j] += a.p;
				}
			}
		}

		return inv;
	}

	friend ostream& operator <<(ostream &out, const ModMatrix &a) {
		for(int i = 0; i < a.m; ++i) {
			for(int j = 0; j < a.n; ++j) out << a[i][j] << ' ';
			if(i + 1 < a.m) out << '\n';
		}
		return out;
	}
};
