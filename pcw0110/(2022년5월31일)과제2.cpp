#include <iostream>
#include <vector>
#include <cmath>

class Plane
{
private:
	int dimension;
	std::vector <long long> quadrant;
	long long x_to_move;
	long long y_to_move;

public:
	Plane();
	std::vector <long long> getQuadrant();
	void move_X(int dimension, long long to_move);
	void move_Y(int dimension, long long to_move);
	void moveQuadrant();
	void printOut();
};

Plane::Plane()
{
	long long quadrant = 0;
	int dimension = 0;

	std::cin >> dimension >> quadrant;
	std::cin >> x_to_move >> y_to_move;
	this->dimension = dimension;
	for (int i = 0; i < this->dimension; i++)
	{
		long long index = std::pow(10, --dimension);
		if (this->quadrant.empty())
			this->quadrant.push_back(quadrant / index);
		else
			this->quadrant.insert(this->quadrant.begin(), (quadrant / index));
		quadrant = quadrant % index;
	}
}

void Plane::move_X(int dimension, long long to_move)
{
	if (this->dimension == dimension)
		return;

	switch (this->quadrant[dimension])
	{
	case 1:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 2;
			move_X(++dimension, (to_move / 2) + (to_move % 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 2;
			move_X(++dimension, -(to_move / 2));
		}
		break;
	case 2:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 1;
			move_X(++dimension, (to_move / 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 1;
			move_X(++dimension, -((to_move / 2)+(to_move%2)));
		}
		break;
	case 3:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 4;
			move_X(++dimension, (to_move / 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 1;
			move_X(++dimension, -((to_move / 2) + (to_move % 2)));
		}
		break;
	case 4:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 3;
			move_X(++dimension, (to_move / 2) + (to_move % 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 3;
			move_X(++dimension, -(to_move / 2));
		}
		break;
	}

	return;
}

void Plane::move_Y(int dimension, long long to_move)
{
	if (this->dimension == dimension)
		return;

	switch (this->quadrant[dimension])
	{
	case 1:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 4;
			move_Y(++dimension, (to_move / 2) + (to_move % 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 4;
			move_Y(++dimension, -(to_move / 2));
		}
		break;
	case 2:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 3;
			move_Y(++dimension, (to_move / 2) + (to_move % 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 3;
			move_Y(++dimension, -(to_move / 2));
		}
		break;
	case 3:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 2;
			move_Y(++dimension, (to_move / 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 2;
			move_Y(++dimension, -((to_move / 2) + (to_move % 2)));
		}
		break;
	case 4:
		if (to_move > 0)
		{
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 1;
			move_Y(++dimension, (to_move / 2));
		}
		else if (to_move < 0)
		{
			to_move = -to_move;
			if (to_move % 2 == 1)
				this->quadrant[dimension] = 1;
			move_Y(++dimension, -((to_move / 2) + (to_move % 2)));
		}
		break;
	}

	return;
}

void Plane::moveQuadrant()
{
	move_X(0, this->x_to_move);
	move_Y(0, this->y_to_move);
	return;
}

void Plane::printOut()
{
	auto reverse_quadrant = this->quadrant;
	while (!reverse_quadrant.empty())
	{
		std::cout << reverse_quadrant.back();
		reverse_quadrant.pop_back();
	}
}

std::vector <long long> Plane::getQuadrant()
{
	return quadrant;
}




int main()
{
	Plane plane;

	plane.moveQuadrant();
	plane.printOut();

	return 0;
}
