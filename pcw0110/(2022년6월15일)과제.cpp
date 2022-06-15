#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


struct Point
{
	double x, y;
	Point(double first, double second) : x(first), y(second) {};
};

std::vector <Point> dots;

int ccw(Point p1, Point p2, Point p3)
{
	int z = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
	if (z < 0)
		return -1;
	else if (z == 0)
		return 0;
	else
		return 1;
}

int getDistance(Point p1, Point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double dotLineDistance(Point p1, Point p2, Point p3)
{
	return abs((p2.x - p1.x)*(p1.y - p3.y) - (p1.x - p3.x)*(p2.y - p1.y)) / sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

bool ccwCompare(Point p1, Point p2)
{
	auto zero = dots[0];
	int z = ccw(zero, p1, p2);
	if (z == 0)
		return getDistance(zero, p1) < getDistance(zero, p2);
	else
		return z > 0;

}


class ConvexHull
{
private:
	std::vector<Point> verts;
	ConvexHull() {};

public:
	ConvexHull(std::vector<Point> inputs);
	void setDots();
	void setVerts();
	std::vector<Point> getVerts() const;
	std::vector<Point> graham();

};

ConvexHull::ConvexHull(std::vector<Point> input)
{
	dots = input;
	setDots();
	setVerts();
}

std::vector<Point> ConvexHull::graham()
{
	std::vector <Point> verts;
	for (int i = 0; i < dots.size(); i++)
	{
		while (2 <= verts.size() && ccw(verts[verts.size() - 2], verts[verts.size() - 1], dots[i]) <= 0)
			verts.pop_back();

		verts.push_back(dots[i]);
	}
	return verts;
}

void ConvexHull::setDots()
{
	int temp = 0;
	for (int i = 1; i < dots.size(); i++)
		if (dots[i].y < dots[temp].y || (dots[i].y == dots[temp].y && dots[i].x < dots[temp].x))
			temp = i;
	std::swap(dots[temp], dots[0]);
	std::sort(dots.begin() + 1, dots.end(), ccwCompare);

	return;
}

void ConvexHull::setVerts()
{
	verts = graham();
	return;
}


std::vector<Point> ConvexHull::getVerts() const
{
	return verts;
}


class GarbageChute
{
private:
	std::vector<Point> trash_shape;

public:
	GarbageChute(std::vector<Point> trash_shape);
	double getMinimumWidth() const;

};

GarbageChute::GarbageChute(std::vector<Point> trash_shape)
{
	this->trash_shape = trash_shape;
}

double GarbageChute::getMinimumWidth() const
{
	int top = trash_shape.size();
	double min_width = 1000000000;
	for (int i = 0; i < top - 1; i++)
	{
		double among_max = 0;
		for (int j = 0; j < top; j++)
		{
			if (i == j || i + 1 == j) continue;
			among_max = std::max(among_max, dotLineDistance(trash_shape[i], trash_shape[i + 1], trash_shape[j]));
		}
		min_width = std::min(min_width, among_max);
	}
	return min_width;
}


int main()
{
	std::cout << std::fixed;
	std::cout.precision(2);
	int num_of_dots = 0;
	double x = 0, y = 0;
	int test_case = 0;

	std::vector <Point> dots;
	std::cin >> num_of_dots;

	while (num_of_dots)
	{
		for (int i = 0; i < num_of_dots; i++)
		{
			std::cin >> x >> y;
			dots.push_back(Point(x, y));
		}
		auto shape = ConvexHull(dots).getVerts();

		/*for (auto i : shape.getVerts())
			std::cout << i.x << " " << i.y << "\n";*/

		auto garbage_chute = GarbageChute(shape);
		double min_width = garbage_chute.getMinimumWidth();


		if (min_width==0)
			std::cout << "Case " << ++test_case << ": " << min_width << "\n";
		else
			std::cout << "Case " << ++test_case << ": " << min_width + 0.005 << "\n";
		std::cin >> num_of_dots;
		dots.clear();
	}
	return 0;
}
