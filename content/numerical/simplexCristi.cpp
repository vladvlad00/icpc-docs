/**
 * Author: Cristi
 */
const ld EPS = 0.00000001;

int n;

struct equation {
	ld b, c[NMAX];

	equation() {
		b = 0;
		memset(c, 0, sizeof c);
	}

	void operator /=(ld val) {
		b /= val;
		for(int i = 0; i < n; ++i) c[i] /= val;
	}

	void print() {
		for(int j = 0; j < n; ++j) cout << c[j] << ' ';
		cout << "--- " << b << '\n';
	}
};

bool basis[NMAX];
equation eq[NMAX], obj;

void printSystem() {
	cout << "*************\n";
	for(int i = 0; i < n; ++i) if(basis[i]) eq[i].print();
	obj.print();
	cout << "*************\n";
}

void transform(int basisVar, int nonbasisVar) {
	eq[nonbasisVar] = eq[basisVar];
	eq[nonbasisVar].c[basisVar] = -1;
	eq[nonbasisVar].c[nonbasisVar] = 0;

	eq[nonbasisVar] /= -eq[basisVar].c[nonbasisVar];

	for(int i = 0; i < n; ++i) {
		if(i == basisVar || i == nonbasisVar || !basis[i]) continue;
		if(fabs(eq[i].c[nonbasisVar]) < EPS) continue;

		// eq[i].c[nonbasisVar]
		for(int j = 0; j < n; ++j) {
			eq[i].c[j] += eq[nonbasisVar].c[j] * eq[i].c[nonbasisVar];
		}

		eq[i].b += eq[nonbasisVar].b * eq[i].c[nonbasisVar];
		eq[i].c[nonbasisVar] = 0;
	}

	// objective
	for(int j = 0; j < n; ++j) {
		obj.c[j] += eq[nonbasisVar].c[j] * obj.c[nonbasisVar];
	}

	obj.b += eq[nonbasisVar].b * obj.c[nonbasisVar];
	obj.c[nonbasisVar] = 0;

	basis[basisVar] = false;
	basis[nonbasisVar] = true;
}

pair<bool, int> getMax(int j) {
//    dbg(j);
	pair<bool, int> ret = { false, 0 };

	for(int i = 0; i < n; ++i)
		if(basis[i] && eq[i].c[j] < 0) {
			ld maxv = -eq[i].b / eq[i].c[j];
//            dbg(maxv);
			if(!ret.fi || -eq[ret.se].b / eq[ret.se].c[j] > maxv) ret = { true, i };
		}

	return ret;
}

pair<bool, ld> simplex() {
//    printSystem();
	while(true) {
		int j;
		for(j = 0; j < n; ++j)
			if(obj.c[j] > 0) {
				auto ret = getMax(j);
//                dbg(j);
//                dbg(ret);
				if(!ret.fi) return { false, 1 };

				ld val = -eq[ret.se].b / eq[ret.se].c[j];
				// x[j] -> val
				// x[ret.se] -> 0

				transform(ret.se, j);
//                cout << ret.se << ' ' << j << '\n';
//                printSystem();
				break;
			}

		if(j >= n) break;
	}

	return { true, obj.b };
}

int main() {
	int i, j, var, m, nreq, a, b, c;

	cin >> var >> m;
	nreq = var - 2;
	n = m + 2 * nreq + m;

	// dbg(n);
	// dbg(m);
	// dbg(var);

	for(i = 0; i < m; ++i) {
		cin >> a >> b >> c;

		eq[m + 2 * nreq + i].c[i] = -1;
		eq[m + 2 * nreq + i].b = c;

		if(a == 1) obj.c[i] = 1;
		if(b == 1) obj.c[i] = -1;
		if(a != 1 && a != var) eq[m + a - 2].c[i] = 1, eq[m + nreq + a - 2].c[i] = -1;
		if(b != 1 && b != var) eq[m + b - 2].c[i] = -1, eq[m + nreq + b - 2].c[i] = 1;
	}
	
	for(i = m; i < n; ++i) basis[i] = true;
	// printSystem();

	auto ret = simplex();

	cout << obj.b << '\n';
	for(int j = 0; j < m; ++j) cout << fixed << setprecision(7) << (basis[j] ? (int) eq[j].b : 0) << ' ';
	cout << '\n';

	return 0;
}
