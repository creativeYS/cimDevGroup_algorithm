#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include <queue>
#include <math.h>
#include<cmath>

struct Point
{
	int x, y, dx, dy;
	Point(int x, int y, int dx = 0, int dy = 0)
		: x(x), y(y), dx(dx), dy(dy) {}

	bool operator<(const Point& point) {
		if (this->dy*point.dx != this->dx*point.dy)
			return this->dy*point.dx < this->dx*point.dy;
		if (this->y != point.y)
			return this->y < point.y;
		return this->x < point.x;
	}
};

class Helper
{
public:
	int CCW(Point p1, Point p2, Point p3) {
		double ccwRes = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
		if (ccwRes > 0) return 1;
		else if (ccwRes < 0) return -1;
		else return 0;
	}

	double findMin(std::vector<double> doubleVector) {

		double minValue = 0x3f3f3f3f;
		for (int i = 0; i < doubleVector.size(); i++)
			if (minValue > doubleVector[i]) minValue = doubleVector[i];

		return minValue;
	}
};


class convexHull
{
private:
	std::vector<Point> polygon;
	int numberOfPoint;
	double const findLongestHeight(Point p1, Point p2) const;

public:
	void const makeConvexHull(std::vector<Point> inputData, int numberOfPoint);
	double const findMinHeight();
	Helper helper{};
};



void const convexHull::makeConvexHull(std::vector<Point> inputData, int numberOfPoint) {

	this->numberOfPoint = numberOfPoint;

	std::sort(inputData.begin(), inputData.end());

	for (int i = 1; i < numberOfPoint; i++) {
		inputData[i].dx = inputData[i].x - inputData[0].x;
		inputData[i].dy = inputData[i].y - inputData[0].y;
	}

	std::sort(inputData.begin() + 1, inputData.end());

	std::stack<int> s;

	s.push(0);
	s.push(1);

	int next = 2;

	while (next < numberOfPoint) {
		while (s.size() >= 2) {
			int second = s.top();
			s.pop();
			int first = s.top();

			if (helper.CCW(inputData[first], inputData[second], inputData[next]) > 0) { // ccw 방향인 경우 // cw 방향일 경우 second를 버리고
				s.push(second);
				break;
			}
		}
		s.push(next++);
	}

	long ssize = s.size();
	for (int i = 0; i < ssize; i++) {
		polygon.push_back(inputData[s.top()]);
		s.pop();
	}
}


double const convexHull::findLongestHeight(Point p1, Point p2) const { //각 선분에서 각 점으로 가장 긴 거리

	double height = 0;

	double A = p1.y - p2.y;
	double B = p2.x - p1.x;
	double C = p1.x*p2.y - p2.x*p1.y;

	for (int i = 0; i < polygon.size(); i++) {
		double res = std::abs(A*polygon[i].x + B * polygon[i].y + C) / (std::sqrt(A*A + B * B));
		height = std::max(height, res);
	}

	return height;
}

double const convexHull::findMinHeight() {

	std::vector<double> distGroup;

	for (int i = 0; i < polygon.size(); i++) {
		distGroup.push_back(findLongestHeight(polygon[i], polygon[(i + 1) % polygon.size()])); // 한 선분에서 각 점까지의 가장 먼 거리
	}

	return helper.findMin(distGroup);
}


int main() {

	int numOfPoint = 1;
	int caseCounter = 1;
	while (numOfPoint) {
		std::cin >> numOfPoint;
		if (numOfPoint == 0) return 0;
		std::vector<Point> inputData;

		for (int i = 0; i < numOfPoint; i++) {
			int x, y;
			std::cin >> x >> y;
			Point inputPoint{ x,y };
			inputData.push_back(inputPoint);
		}

		convexHull polygon{};
		polygon.makeConvexHull(inputData, numOfPoint);
		double result = polygon.findMinHeight();
		std::cout << std::fixed;
		std::cout.precision(2);
		std::cout << "Case " << caseCounter << ": " << ceil(result * 100) / 100 << "\n";
		caseCounter++;
	}
}
