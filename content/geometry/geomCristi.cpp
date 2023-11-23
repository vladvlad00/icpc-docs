const ld EPS = 1e-9;
const ld PI = acos(-1);

struct Point {
	ld x, y;

	Point(ld x = 0, ld y = 0) : x(x), y(y) {}

	Point operator +(const Point &p) const { return { x + p.x, y + p.y }; }
	Point operator -(const Point &p) const { return { x - p.x, y - p.y }; }
	friend Point operator *(ld a, const Point &p) { return { a * p.x, a * p.y }; }
	Point operator /(ld a) const { return { x / a, y / a }; }

	friend istream& operator >>(istream &in, Point &p) { return in >> p.x >> p.y; }
	friend ostream& operator <<(ostream &out, const Point &p) { return out << "Point(" << p.x << ' ' << p.y << ')'; }

	friend bool between(const Point &a, const Point &b, const Point &c) {
		return min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x) && min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
	}

	friend ld dist(const Point &a, const Point &b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	friend ld ccw(const Point &a, const Point &b, const Point &c) {
		return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	}
};

Point polar(ld alpha, ld r = 1) {
	return { r * cos(alpha), r * sin(alpha) };
}

struct Point3D {
	ld x, y, z;

	Point3D(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}

	friend Point3D operator -(const Point3D &a, const Point3D &b) { return Point3D(a.x - b.x, a.y - b.y, a.z - b.z); }
	friend Point3D crossProduct(const Point3D &a, const Point3D &b) { return Point3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
	friend istream& operator >>(istream &in, Point3D &p) { return in >> p.x >> p.y >> p.z; }
	friend ostream& operator <<(ostream &out, const Point3D &p) { return out << "Point3D(" << p.x << ' ' << p.y << ' ' << p.z << ')'; }

	friend ld dist(const Point3D &a, const Point3D &b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}
};

struct Line {
	ld a, b, c;

	Line(Point p = {0, 0}, Point q = {0, 0}) {
		a = q.y - p.y;
		b = p.x - q.x;
		c = -a * p.x - b * p.y;
		//assert(abs(a * q.x + b * q.y + c) < EPS);
	}

	friend ostream& operator <<(ostream &out, const Line &l) { return out << "Line(" << l.a << ' ' << l.b << ' ' << l.c << ')'; }

	friend Point intersect(const Line &l1, const Line &l2) {
		ld y = (l2.c * l1.a - l1.c * l2.a) / (l1.b * l2.a - l2.b * l1.a);

		if(l1.a) return { -(l1.c + l1.b * y) / l1.a, y };
		else return { -(l2.c + l2.b * y) / l2.a, y };
	}

	friend bool parallel(const Line &l1, const Line &l2) {
		return abs(l1.b * l2.a - l2.b * l1.a) < EPS;
	}
	
	friend ld dist(const Line &l, const Point &p) {
		return abs(l.a * p.x + l.b * p.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
	}
};

struct Circle {
	Point p;
	ld r;

	friend vector<Point> intersect(const Circle &c1, const Circle &c2) {
		// not handling the case when circles are tangent... (returning empty)
		ld d = dist(c1.p, c2.p);

		if(d > c1.r + c2.r - EPS) return {};
		if(d + min(c1.r, c2.r) < max(c1.r, c2.r) + EPS) return {};

		ld d1 = (d * d - c2.r * c2.r + c1.r * c1.r) / (2 * d);
		ld h = sqrt(c1.r * c1.r - d1 * d1);

		Point i = (c2.p - c1.p) / d;
		Point j = { -i.y, i.x };
		return { c1.p + d1 * i + h * j, c1.p + d1 * i - h * j };
	}

	friend bool inside(const Circle &c1, const Circle &c2) {
		ld d = dist(c1.p, c2.p);
		return d + c1.r < c2.r + EPS;
	}

	friend bool inside(const Point &p, const Circle &c) {
		return dist(p, c.p) < c.r + EPS;
	}
};

struct Plane {
	ld a, b, c, d;

	Plane(Point3D p, Point3D q, Point3D r) {
		Point3D n = crossProduct(q - p, r - p);
		a = n.x;
		b = n.y;
		c = n.z;
		d = -(p.x * a + p.y * b + p.z * c);
	}

	friend ld dist(const Plane &pl, const Point3D &p) {
		return abs(pl.a * p.x + pl.b * p.y + pl.c * p.z + pl.d) / sqrt(pl.a * pl.a + pl.b * pl.b + pl.c * pl.c);
	}
};
