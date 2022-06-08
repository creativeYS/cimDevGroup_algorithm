#include <iostream>

struct Point
{
	int x;
	int y;
};

class Lines
{
private:
	Point xy[4];

public:
	void initiate();
	int ccw(Point xy1, Point xy2, Point xy3);
	bool is_Crossed();
	void print_XY();
};

void Lines::initiate()
{
	for (int i = 0; i < 4; i++)
		std::cin >> xy[i].x >> xy[i].y;
}

int Lines::ccw(Point xy1, Point xy2, Point xy3)
{
	
	int z = (xy2.x - xy1.x)*(xy3.y - xy1.y) - (xy2.y - xy1.y)*(xy3.x - xy1.x);

	if (z > 0)
		return 1;
	else if (z < 0)
		return -1;
	else
		return 0;
}

bool Lines::is_Crossed()
{
	if (ccw(xy[0], xy[1], xy[2]) * ccw(xy[0], xy[1], xy[3]) < 0)
		return true;
	else
		return false;
}

void Lines::print_XY()
{
	for(int i=0; i<2; i++)
		std::cout << xy[i].x << " " << xy[i].y << std::endl;
	std::cout << std::endl;
	for (int i = 2; i < 4; i++)
		std::cout << xy[i].x << " " << xy[i].y << std::endl;

}


int main()
{
	Lines vector{};
	vector.initiate();
	if (vector.is_Crossed())
		std::cout << "1";
	else
		std::cout << "0";

	return 0;
}
