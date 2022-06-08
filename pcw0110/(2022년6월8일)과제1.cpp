#include <iostream>
#include <vector>
#include <algorithm>

class Pile
{
private:
	std::vector<std::vector<int>> rows;
	std::vector<std::vector<int>> columns;
	int total_blocks;

public:
	Pile(const int & num_of_rows, const int & num_of_columns);

	void initiate(const int & num_of_rows, const int & num_of_columns);
	std::vector<std::vector<int>> get_Vector(std::string input) const;
	void print_Vector(std::string input) const;
	int get_Area() const;
	int get_Duplicated(std::string input) const;
	int get_Height_dup() const;
};

Pile::Pile(const int & num_of_rows, const int & num_of_columns)
{
	total_blocks = 0;
	try	{
		initiate(num_of_rows, num_of_columns);
	}
	catch (std::string e)	{
		return;
	}

	for (int i = 0; i < num_of_rows; i++)
	{
		for (int j = 0; j < num_of_columns; j++)
		{
			std::cin >> rows[i][j];
			columns[j][i] = rows[i][j];
			total_blocks += rows[i][j];
		}
	}
}

void Pile::initiate(const int & num_of_rows, const int & num_of_columns)
{
	rows.assign(num_of_rows, std::vector<int>(num_of_columns));		// rows 2차원 벡터를 n_row * n_col 크기만큼 0으로 초기화
	columns.assign(num_of_columns, std::vector<int>(num_of_rows));	// columns 2차원 벡터를 n_col * n_row 크기만큼 0으로 초기화
}

std::vector<std::vector<int>> Pile::get_Vector(std::string input) const
{
	if (input.compare("rows") == 0)
		return rows;
	else if (input.compare("columns") == 0)
		return columns;
	else
		throw input;
}

void Pile::print_Vector(std::string input) const
{
	std::vector<std::vector<int>> temp;
	temp = (input=="rows") ? rows : columns;
	for (auto row : temp)
	{
		for (auto element : row)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
}

int Pile::get_Duplicated(std::string input) const
{
	std::vector<std::vector<int>> temp;
	int duplicated = 0;
	
	temp = (input.compare("rows")) ? rows : columns;
	for (int i = 0; i < temp.size(); i++)
		for (int j = 0; j < temp[i].size() - 1; j++)
			duplicated += std::min(temp[i][j], temp[i][j+1])*2;

	return duplicated;
}

int Pile::get_Height_dup() const
{
	int duplicated = 0;

	for (auto row : rows)
		for (auto element : row)
			duplicated += (element - 1) * 2;
	
	return duplicated;
}

int Pile::get_Area() const
{
	int duplicated = get_Duplicated("rows") + get_Duplicated("columns") + get_Height_dup();
	return (total_blocks * 6) - duplicated;
}

int main()
{
	int rows = 0;
	int columns = 0;
	std::cin >> rows >> columns;
	auto blocks = new Pile(rows, columns);

	std::cout << blocks->get_Area() << std::endl;

	return 0;
}
