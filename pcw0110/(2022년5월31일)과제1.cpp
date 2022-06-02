#include <iostream>

class Cartesian
{
private:
	int x;
	int y;

public:
	Cartesian();
	Cartesian(int x, int y);
	int getQuadrant();
	void printQuadrant();
};

Cartesian::Cartesian()
{
	std::cin >> x >> y;
}


Cartesian::Cartesian(int x, int y)
{
	this->x = x;
	this->y = y;
}


int Cartesian::getQuadrant()
{
	int quadrant = 0;

	if (x > 0)
	{
		if (y > 0)
			quadrant = 1;
		else if (y < 0)
			quadrant = 4;
	}
	else if (x < 0)
	{
		if (y > 0)
			quadrant = 2;
		else if (y < 0)
			quadrant = 3;
	}

	return quadrant;
}

void Cartesian::printQuadrant()
{
	std::cout << getQuadrant() << std::endl;
	return;
}



int main()
{
	Cartesian coordinate_system;
	coordinate_system.printQuadrant();
}
