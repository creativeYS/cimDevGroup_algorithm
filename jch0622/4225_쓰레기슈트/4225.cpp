#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

#define PI acos(-1)
#define EPSILON 0.00001

enum Ccw { CW, CCW, EQUAL, OPPOSITE };

// CAD에서 실제로 polygon을 수정한다고 가정

class Point2
{
private:
	double x;
	double y;
	Point2() { }

public:
	Point2(const double & x, const double & y) : x(x), y(y) { }
	Point2(const Point2 & src) : x(src.getX()), y(src.getY()) { }
	~Point2() { }

	double getX() const { return this->x; }
	double getY() const { return this->y; }
	void setX(const int & x) { this->x = x; }
	void setY(const int & y) { this->y = y; }

	Point2 & operator=(Point2 const & rhs)
	{
		this->x = rhs.getX();
		this->y = rhs.getY();
		return *this;
	}

	Point2 operator-(const Point2 & rhs) const
	{
		return Point2(this->getX() - rhs.getX(), this->getY() - rhs.getY());
	}

	// 0으로 나눌 경우에 대한 예외처리 필요해보임
	Point2 operator/(const double & value) const
	{
		return Point2(this->getX() / value, this->getY() / value);
	}

	// 거리
	double dist(const Point2 & point) const
	{
		double x = this->x - point.x;
		double y = this->y - point.y;
		return sqrt(x * x + y * y);
	}

	double dist() const
	{
		return sqrt(this->x * this->x + this->y * this->y);
	}

	// 방향벡터화
	Point2 normalize() const
	{
		return (*this) / dist();
	}

	// 현재 점을 기준으로 p1과 p2사이의 각도 찾기
	double findAngle(const Point2 & p1, const Point2 & p2) const
	{
		const Point2 normalVector1 = (p1 - *this).normalize();
		const Point2 normalVector2 = (p2 - *this).normalize();

		double cosTheta = normalVector1.innerProduct(normalVector2);
		return acos(cosTheta);
	}

	// 현재 점을 기준으로 p1에서 p2의 방향 찾기
	int ccw(const Point2 & p1, const Point2 & p2) const
	{
		double vec1 = this->outerProductZValue(p1, p2);
		if (vec1 > 0)
			return CCW;
		else if (vec1 < 0)
			return CW;
		else if (this->findAngle(p1, p2) < EPSILON)
			return EQUAL;
		else
			return OPPOSITE;
	}

	// 내적값
	double innerProduct(const Point2 & p1, const Point2 & p2) const
	{
		const Point2 vec1(p1 - (*this));
		const Point2 vec2(p2 - (*this));
		return vec1.getX() * vec2.getX() + vec1.getY() * vec2.getY();
	}

	double innerProduct(const Point2 & vec) const
	{
		return this->getX() * vec.getX() + this->getY() * vec.getY();
	}

	// 외적 z값
	double outerProductZValue(const Point2 & p1, const Point2 & p2) const
	{
		const Point2 vec1(p1 - (*this));
		const Point2 vec2(p2 - (*this));
		return vec1.getX() * vec2.getY() - vec2.getX() * vec1.getY();
	}

	double outerProductZValue(const Point2 & vec) const
	{
		return this->getX() * vec.getY() - vec.getX() * this->getY();
	}

	// 점과 직선 사이의 거리
	double lineToPointDistance(const Point2 & p1, const Point2 & p2) const
	{
		// this-> 해당 점
		double angle = p1.findAngle(*this, p2);
		return p1.dist(*this) * sin(angle);
	}
};


// 순서대로 선 이어진다고 가정
class Polygon
{
private:
	const int numberOfSide;
	std::vector<Point2> node;
	Polygon();

public:

	Polygon(const int & numberOfSide, const std::vector<Point2> & node) : numberOfSide(numberOfSide), node(node) { }
	Polygon(const Polygon & src) : numberOfSide(src.getNumberOfSide()), node(src.getNode()) {}
	~Polygon() {}

	Point2 & operator[](const int & index)
	{
		return node[index];
	}

	const int getNumberOfSide() const { return numberOfSide; }
	const std::vector<Point2> getNode() const { return node; }

	// 원하는 답
	double polygonMinWidth() const
	{
		// 볼록껍질의 지점까지 이동하는 함수
		std::pair<int, int> index = this->findFirstConvexPoint();
		int startIndex = index.first;
		int nextIndex = index.second;

		// 첫 시작만 반복문 밖에서
		double minWidth = this->polygonWidth(startIndex, nextIndex);
		int curIndex = nextIndex;

		while (startIndex != curIndex)
		{
			nextIndex = this->findConvexPoint(curIndex);
			minWidth = std::min(polygonWidth(curIndex, nextIndex), minWidth);
			curIndex = nextIndex;
		}
		return minWidth;
	}

	int findNextIndex(const int & index) const
	{
		return this->findConvexPoint(index);
	}

	// 특정 점 -> 선분, 선분을 기준으로 가장 짧은 폭
	double polygonWidth(const int & index, const int & nextIndex) const
	{
		double maxWidth = 0.0;
		for (int i = 0; i < this->numberOfSide; i++)
		{
			if (i == index || i == nextIndex)
				continue;
			double dist = this->node[i].lineToPointDistance(this->node[index], this->node[nextIndex]);
			maxWidth = std::max(maxWidth, dist);
		}
		return maxWidth;
	}

	// find 볼록껍질까지의 지점
	std::pair<int, int> findFirstConvexPoint() const
	{
		for (int i = 0; i < this->numberOfSide; i++)
		{
			int nextIndex = this->findConvexPoint(i);
			if (nextIndex >= 0)
				return std::make_pair(i, nextIndex);
		}
		return std::make_pair(-1, -1);
	}

	// 볼록 껍질의 Node인지 판별
	int findConvexPoint(const int & index) const
	{
		const int indexNext = (index + 1) % this->numberOfSide;
		std::vector<double> angleVec = { 0.0, 0.0, 0.0, 0.0 };
		std::vector<int> idxVec = { -1, -1, indexNext, -1 };
		double parallelDist = 0;

		for (int i = 0; i < this->numberOfSide; i++)
		{
			if (i == index || i == indexNext)
				continue;
			const double angle = this->node[index].findAngle(this->node[indexNext], this->node[i]);
			const int ccwValue = this->node[index].ccw(this->node[indexNext], this->node[i]);

			if (ccwValue == EQUAL && parallelDist < this->node[index].dist(this->node[i]))
			{
				parallelDist = this->node[index].dist(this->node[i]);
				idxVec[ccwValue] = i;
			}
			else if (angleVec[ccwValue] < angle)
			{
				angleVec[ccwValue] = angle;
				idxVec[ccwValue] = i;
			}
		}
		if (idxVec[OPPOSITE] >= 0 || angleVec[CW] + angleVec[CCW] > PI + EPSILON)
			return -1;
		else if (idxVec[CW] >= 0)
				return idxVec[CW];
		else
			return idxVec[EQUAL];
	}
};

int main()
{
	std::vector<double> answer;

	int numberOfSide;
	std::cin >> numberOfSide;

	while (numberOfSide > 0)
	{
		std::vector<Point2> node(numberOfSide, Point2(0, 0));
		for (int i = 0; i < numberOfSide; i++)
		{
			int x, y;
			std::cin >> x >> y;
			node[i] = Point2(x, y);
		}
		Polygon polygon(numberOfSide, node);
		answer.push_back(polygon.polygonMinWidth());
		std::cin >> numberOfSide;
	}

	for (int i = 0; i < answer.size(); i++)
	{
		std::cout.precision(2);
		std::cout.setf(std::ios::fixed);
		std::cout << "Case " << i + 1 << ": " << ceil((answer[i] - EPSILON) * 100) / 100 << std::endl;
	}
}

// 벡터 각도 구하기
// 두 벡터의 각도 구하기
// 외적 이용해서 왼쪽 오른쪽 방향 파악
// 두 벡터의 각도가 180 초과 -> 오목다각형 부분이라 판별하지 않음
// noexcept 이용해서 복사생성자 안만드는거도 참고해볼 필요가 있을듯