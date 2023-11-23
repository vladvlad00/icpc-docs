/**
 * Author: Cristi
 * Description: wtf
 */
void extendedGCD(int a, int b, int &x, int &y, int mod) {
	if(b == 0) { x = 1; y = 0; return; }

	int xx, yy;
	extendedGCD(b, a % b, xx, yy, mod);

	x = yy;
	y = (xx - 1LL * a / b * yy) % mod;
	if(y < 0) y += mod;
}

int fastCrt(const vector<pii> &eqs) {
	int currm = 1, currr = 0;

	for(const auto &[m, r] : eqs) {
		if(currm == 1) {
			currm = m;
			currr = r;
			continue;
		}

		int x, y;
		extendedGCD(currm, m, x, y, currm * m);

		int a = (1LL * r * x) % m;
		int b = (1LL * currr * y) % currm;

		currr = (1LL * a * currm + 1LL * b * m) % (currm * m);
		currm *= m;
	}

	return currr;
}


