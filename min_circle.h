#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>

struct Point2D {
	double x, y;

	bool operator==(const Point2D& other);
	bool operator!=(const Point2D& other);
};

struct LineSegment {
	Point2D start;
	Point2D end;
};

struct Circle {
	Point2D center;
	double radius;

	bool isValid() const;
	bool contains(const Point2D& point) const;
	bool contains(const LineSegment& segment) const;
	bool containsEntireSegment(const LineSegment& segment) const;	
};	

double distanceSquared(const Point2D& p1, const Point2D& p2);
double distance(const Point2D& p1, const Point2D& p2);
double triangleSquare(const Point2D& p1, const Point2D& p2, const Point2D& p3);
std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments);
Point2D findMidPoint(const LineSegment& segment);

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments);
Circle circleFromDiameter(const Point2D& p1, const Point2D& p2);
Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3);
Circle minCircleHelper(std::vector<Point2D>& points, std::vector<Point2D> boundary, size_t n);
Circle minCircle(std::vector<Point2D> points);

