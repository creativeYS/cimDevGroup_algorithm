#include<iostream>
#include<vector>

class Point
{
private:
	std::pair<int, int> point;
	void setPoint(const int x, const int y);
public:
	Point(const int x, const int y) {
		setPoint(x, y);
	}
	std::pair<int,int> getPoint() const;
};

void Point::setPoint(const int x, const int y) {
	this->point.first = x;
	this->point.second = y;
}

std::pair<int,int> Point::getPoint() const {
	return point;
}


class Solver
{
private:
	std::vector<Point> points;
	int crossResult;
	int CCW(Point p1, Point p2, Point p3) const;
	
public:
	void setPoints(const std::vector<Point> inputData);
	void crossCheck();
	int getPosibility() const;

};

void Solver::setPoints(std::vector<Point> inputData) { points = inputData; }
int Solver::getPosibility() const { return crossResult; };

void Solver::crossCheck() {
	if (
		CCW(points[0], points[1], points[2]) * CCW(points[0], points[1], points[3]) < 0 &&
		CCW(points[2], points[3], points[0]) * CCW(points[2], points[3], points[1]) < 0
		) crossResult = 1;
	else crossResult = 0;
}

int Solver::CCW(Point p1, Point p2, Point p3) const{
	int ccwRes = (p2.getPoint().first - p1.getPoint().first)*(p3.getPoint().second - p1.getPoint().second) - (p2.getPoint().second - p1.getPoint().second)*(p3.getPoint().first - p1.getPoint().first);
	if (ccwRes > 0) return 1;
	else if (ccwRes < 0) return -1;
	else return 0;
}

int main() {

	std::vector<Point> inputData;

	for (int i = 0; i < 4; i++) {
		int x, y;
		std::cin >> x >> y;
		inputData.push_back(Point(x,y));
	}

	Solver solver{};

	solver.setPoints(inputData);
	solver.crossCheck();
	std::cout << solver.getPosibility() << std::endl;

}
