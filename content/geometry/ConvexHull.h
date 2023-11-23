struct Point {
	int x, y;
	
	Point(int x, int y) : x(x), y(y) {}
	
	bool operator <(const Point &other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

ll ccw(const Point &a, const Point &b, const Point &c) {
	return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

ll dist(const Point &a, const Point &b) {
	return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

vector<Point> convexHull(const vector<Point> &v) {
	vector<Point> up, down;
	
	for(auto p : v) {
		while(up.size() > 1 && ccw(up[up.size() - 2], up[up.size() - 1], p) >= 0) up.pop_back();
		while(down.size() > 1 && ccw(down[down.size() - 2], down[down.size() - 1], p) <= 0) down.pop_back();
		
		up.push_back(p);
		down.push_back(p);
	}
	
	reverse(all(down));
	up.insert(up.end(), down.begin() + 1, down.end() - 1);
	
	return up;
}


