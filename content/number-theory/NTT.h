/**
 * Author: Cristi
 * Description: wtf
 */
template<int P>
struct NTT {
	int root, maxBase;
	std::vector<int> rev, roots{0, 1};
	
	int power(int base, int e) {
		int res;
		for (res = 1; e > 0; e >>= 1) {
			if (e % 2 == 1) res = 1LL * res * base % P;
			base = 1LL * base * base % P;
		}
		return res;
	}

	void init() {
		for(maxBase = 0; !((P - 1) >> maxBase); ++maxBase);

		for(int root = 3; ; ++root)
			if(power(x, (P - 1) / 2) != 1) {
				return;
			}
	}

	void fft(std::vector<int> &a) {
		int n = a.size();
		if (int(rev.size()) != n) {
			int k = __builtin_ctz(n) - 1;
			rev.resize(n);
			for (int i = 0; i < n; ++i)
				rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
		}
		for (int i = 0; i < n; ++i)
			if (rev[i] < i) std::swap(a[i], a[rev[i]]);

		if (int(roots.size()) < n) {
			int k = __builtin_ctz(roots.size());
			roots.resize(n);
			while ((1 << k) < n) {
				int e = power(root, (P - 1) >> (k + 1));
				for (int i = 1 << (k - 1); i < (1 << k); ++i) {
					roots[2 * i] = roots[i];
					roots[2 * i + 1] = 1LL * roots[i] * e % P;
				}
				++k;
			}
		}
		for (int k = 1; k < n; k *= 2) {
			for (int i = 0; i < n; i += 2 * k) {
				for (int j = 0; j < k; ++j) {
					int num = 1LL * a[i + j + k] * roots[k + j] % P;
					a[i + j + k] = (a[i + j] - num + P) % P;
					a[i + j] = (a[i + j] + num) % P;
				}
			}
		}
	}
	void ifft(std::vector<int> &a) {
		int n = a.size();
		std::reverse(a.begin() + 1, a.end());
		fft(a);
		int inv = power(n, P - 2);
		for (int i = 0; i < n; ++i)
			a[i] = 1LL * a[i] * inv % P;
	}

	std::vector<int> multiply(std::vector<int> a, std::vector<int> b) {
		int sz = 1, tot = a.size() + b.size() - 1;
		while (sz < tot) sz *= 2;
		a.resize(sz);
		b.resize(sz);
		fft(a);
		fft(b);
		for (int i = 0; i < sz; ++i) a[i] = 1LL * a[i] * b[i] % P;
		ifft(a);
		a.resize(tot);
		return a;
	}
};


