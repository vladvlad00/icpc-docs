/**
 * Author: Cristi
 * Description: wtf
 */
const int L = 200010;
const int LOGL = 18;

int sa[L];
int p[LOGL][L];

void buildSA(const string &s) {
	int n = s.length();
	for(int j = 0; j < n; ++j) p[0][j] = s[j];

	for(int i = 0; i + 1 < LOGL; ++i) {
		vector<pair<pii, int>> v;
		for(int j = 0; j < n; ++j)
			v.push_back({{p[i][j], j + (1 << i) < n ? p[i][j + (1 << i)] : -1}, j});
		sort(all(v));

		for(int j = 0; j < n; ++j)
			p[i + 1][v[j].se] = (j && v[j - 1].fi == v[j].fi ? p[i + 1][v[j - 1].se] : j);
	}

	for(int j = 0; j < n; ++j) sa[p[LOGL - 1][j]] = j;

	for(int i = 0, k = 0; i < n; ++i)
		if(p[LOGL - 1][i] != n - 1) {
			for(int j = sa[p[LOGL - 1][i] + 1]; i + k < n && j + k < n && s[i + k] == s[j + k]; ) ++k;
			//lcp[p[LOGL - 1][i]] = k;
			if(k) --k;
		}
}


