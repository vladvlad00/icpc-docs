/**
 * Author: Vlad
 * Description: wtf
 */

struct pt {
    long double x, y;

    pt(long double x=0, long double y=0) : x(x), y(y){}

    bool operator<(const pt& b) const
    {
        if (abs(x - b.x) > EPS)
            return x < b.x;
        return y < b.y;
    }

    bool operator==(pt p) const { return abs(x - p.x) < EPS && abs(y - p.y) < EPS; }
    pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
    long double cross(pt p) const { return x * p.y - y * p.x; }
    long double cross(pt a, pt b) const { return (a - *this).cross(b - *this); }
};

vector<pt> convex_hull(vector<pt> pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<pt> h(pts.size() + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (pt p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= EPS) t--;
            h[t++] = p;
        }
    return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}