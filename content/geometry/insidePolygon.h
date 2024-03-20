/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-22
 * License: CC0
 * Source: Basic geometry
 * Description: Returns 0 if on polygon, 1 if inside polygon and -1 if outside.
 * Time: O(n)
 * Status: tested with unitTest and Kattis problems copsrobbers, pointinpolygon and intersection
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

int InsidePolygon(vector<Point> P, const Point& p) {
	int ic = 0, n = P.size();
  for (int i = 0, j = n - 1; i < n; j = i++) {
		if (OnSegment(P[i], P[j], p)) return 0;
		ic += (max(P[i].Y(), P[j].Y()) > p.Y() &&
           min(P[i].Y(), P[j].Y()) <= p.Y() &&
          (det(P[i], P[j], p) > 0) == (P[i].Y() <= p.Y()));
	}
  return ic % 2 ? 1 : -1; //inside if odd number of intersections
}
