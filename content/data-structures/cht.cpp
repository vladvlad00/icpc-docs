/**
 * Author: Cristian Vintur
 * Description: Add lines of the form ax+b and query maximum. Lines should be sorted in increasing order of slope
 * Time: $O(\log N)$.
 */
struct Hull {
	int nr = 0;
	vector<pll> v;
	
	void add(pll line) {
		line.se = -line.se;

		while(nr >= 2 && ccw(v[nr - 2], v[nr - 1], line) <= 0) --nr, v.pop_back();
		v.push_back(line);
		++nr;
	}
	
	ll query(ll x) const {
		int l, r, mid;
		for(l = 0, r = nr - 1; l < r; ) {
			mid = (l + r) / 2;
			// care at overflow !!
			if(v[mid + 1].se - v[mid].se < x * (v[mid + 1].fi - v[mid].fi)) l = mid + 1;
			else r = mid;
		}
		// while(p + 1 < nr && eval(v[p + 1], x) < eval(v[p], x)) ++p;
		return eval(v[l], x);
	}

	ll eval(pll line, ll x) const {
		return line.fi * x - line.se;
	}

	ld ccw(const pll &a, const pll &b, const pll &c) const {
		return 1.0 * (b.fi - a.fi) * (c.se - a.se) - 1.0 * (c.fi - a.fi) * (b.se - a.se);
	}
};
