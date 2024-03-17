/**
 * Author: Cristi
 * Description: ceva
 */

const ld EPS = 1e-9;
/**
	* eqs
	*   list of equations, the last element of each row being the free term column of the system
	*/
vector<ld> solve(vector<vector<ld>> &eqs) {
	int m = eqs.size(), n = eqs[0].size();

	for(int i = 0, j = 0; i < m && j < n - 1; ++i, ++j) {
		for(int k = i + 1; k < m; ++k) if(eqs[k][j] > eqs[i][j]) eqs[i].swap(eqs[k]);
		if(abs(eqs[i][j]) < EPS) { --i; continue; }

		for(int k = i + 1; k < m; ++k) {
			ld x = -eqs[k][j] / eqs[i][j];
			for(int l = j; l < n; ++l) eqs[k][l] += eqs[i][l] * x;
		}
	}

	vector<ld> x(n - 1, -1);
	for(int i = m - 1; i >= 0; --i) {
		int j;
		for(j = 0; j < n - 1; ++j) if(abs(eqs[i][j]) > EPS) break;
		if(j == n - 1) continue;

		x[j] = eqs[i][n - 1];
		for(int l = j + 1; l < n - 1; ++l)
			if(abs(eqs[i][l]) > EPS && x[l] < 0) { x[j] = -1; break; }
			else x[j] -= x[l] * eqs[i][l];
		if(x[j] >= 0) x[j] /= eqs[i][j];
	}

	return x;
}
