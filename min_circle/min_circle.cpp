#include "min_circle.h"

bool Point2D::operator==(const Point2D& other) {
	if (x == other.x && y == other.y) return true;
	return false;
}

bool Point2D::operator!=(const Point2D& other) {
	return !(*this == other);
}

bool Circle::isValid() const {
	return radius >= 0;
}

bool Circle::contains(const Point2D& point) const {
	if (!isValid()) return false;
	return (distance(point, center) <= radius);
}

bool Circle::contains(const LineSegment& segment) const {
	if (!isValid()) return false;
	return (distance(segment.start, center) <= radius && distance(segment.end, center) <= radius);
}

bool Circle::containsEntireSegment(const LineSegment& segment) const {
	bool isStart = distance(segment.start, center) <= radius;
	bool isEnd = distance(segment.end, center) <= radius;
	bool isMid = distance(findMidPoint(segment), center) <= radius;
	return (isStart && isMid && isEnd);
}

double distanceSquared(const Point2D& p1, const Point2D& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double distance(const Point2D& p1, const Point2D& p2) {
	return std::sqrt(distanceSquared(p1, p2));
}

std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments) {
	std::vector<Point2D> points;
	for(int i = 0; i < segments.size(); i++) {
		points.push_back(segments[i].start);
		points.push_back(findMidPoint(segments[i]));	
		points.push_back(segments[i].end);
	}
	return points;
}

Point2D findMidPoint(const LineSegment& segment) {
	return Point2D{segment.start.x +(segment.end.x - segment.start.x)/2, segment.start.y +(segment.end.y - segment.start.y)/2}; 	
}


Circle circleFromDiameter(const Point2D& p1, const Point2D& p2) {
	return Circle{findMidPoint({p1, p2}), distance(p1, p2) / 2};
}


Circle circleFrom3Points(const Point2D& p1, const Point2D& p2, const Point2D& p3) {
	double a = p2.x - p1.x;
	double b = p2.y - p1.y;
	double c = p3.x - p1.x;
	double d = p3.y - p1.y;
	double e = a*(p1.x+p2.x) + b*(p1.y+p2.y);
	double f = c*(p1.x+p3.x) + d*(p1.y+p3.y);
	double g = 2 * (a*(p3.y-p2.y) - b*(p3.x-p2.x));
	if (g == 0) return Circle{{0,0}, 0};

	double Cx = (d*e - b*f) / g;
	double Cy = (a*f - c*e) / g;
	Point2D center{Cx, Cy};
	return Circle{center, distance(center, p1)};		       
}

Circle minCircleHelper(std::vector<Point2D>& points, std::vector<Point2D> boundary, size_t n) {
	if (boundary.size() == 3) return circleFrom3Points(boundary[0], boundary[1], boundary[2]);
	if (n == 0) {
		if (boundary.size() == 2) return circleFromDiameter(boundary[0], boundary[1]);
		else if (boundary.size() == 1) return Circle{boundary[0], 0};
		else return Circle{{0, 0}, -1};
	}

	Circle minC = minCircleHelper(points, boundary, n-1);
	if (!minC.contains(points[n-1])) { 
		boundary.push_back(points[n-1]);
		return minCircleHelper(points, boundary, n-1);
	}
	return minC;
}

Circle minCircle(std::vector<Point2D> points) {
	return minCircleHelper(points, {}, points.size());
}

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments) {
	std::vector<Point2D> vec = extractPointsFromSegments(segments);
	return minCircle(vec);
}
