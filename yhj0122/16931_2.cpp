#include<iostream>
#include<vector>

class BoxLine
{
private:
	int height;
	int width;

public:
	void setHeightWidth(int numOfBoxs);
	void refineWidth(int minusNum);
	int getHeight() const;
	int getWidth() const;
};

void BoxLine::setHeightWidth(int numOfBoxs) {
	height = numOfBoxs;
	width = 4 * height + 2;
}

void BoxLine::refineWidth(int minusNum) {
	width -= minusNum;
}

int BoxLine::getWidth() const { return width; }

int BoxLine::getHeight() const { return height; }

///////////////////////////////////////////////////////////////

class Solver
{
private:
	std::vector<std::vector<BoxLine>> boxData;
	int totalWidth;
	void compareFourWay(int y, int x);
	bool isSafeRange(int my, int mx) const;
public:
	void setBoxData(std::vector<std::vector<BoxLine>> inputBoxData);
	void calculateTotalWidth();
	int getTotalWidth() const;

};

void Solver::setBoxData(std::vector<std::vector<BoxLine>> inputBoxData) {
	boxData = inputBoxData;
}
int Solver::getTotalWidth() const { return totalWidth; }

bool Solver::isSafeRange(int my, int mx) const{ // 범위 안전 확인
	if (my >= 0 && my < boxData.size() && mx >= 0 && mx < boxData[0].size()) return true;
	else return false;

}

void Solver::compareFourWay(int y, int x) {
	int my[4] = { -1, 1, 0, 0, }; // 위 아래 왼쪽 오른쪽
	int mx[4] = { 0, 0, -1, 1 };

	for (int i = 0; i < 4; i++) {
		if (isSafeRange(y + my[i], x + mx[i])) {
			if (boxData[y + my[i]][x + mx[i]].getHeight() <= boxData[y][x].getHeight()) { // 주변이 나보다 낮거나 같은 경우
				boxData[y][x].refineWidth(boxData[y + my[i]][x + mx[i]].getHeight());
			}
			else if (boxData[y + my[i]][x + mx[i]].getHeight() > boxData[y][x].getHeight()) { // 주변이 나보다 높은 경우
				boxData[y][x].refineWidth(boxData[y][x].getHeight());
			}
		}
	}
}

void Solver::calculateTotalWidth() {
	int calculatedWidth = 0;
	for (int i = 0; i < boxData.size(); i++) {
		for (int j = 0; j < boxData[0].size(); j++) {
			compareFourWay(i, j);
			calculatedWidth += boxData[i][j].getWidth();
		}
	}
	totalWidth = calculatedWidth;
}

///////////////////////////////////////////////////

int main() {

	int rowNum = 0;
	int colNum = 0;
	int surfaceWidth = 0;

	std::cin >> rowNum >> colNum;
	std::vector<std::vector<BoxLine>> inputBoxData;

	for (int i = 0; i < rowNum; i++) {
		std::vector<BoxLine> temBoxLine;
		for (int j = 0; j < colNum; j++) {
			int numOfBoxs;
			std::cin >> numOfBoxs;
			BoxLine boxLine{};
			boxLine.setHeightWidth(numOfBoxs);
			temBoxLine.push_back(boxLine);
		}
		inputBoxData.push_back(temBoxLine);
	}

	Solver solver{};
	solver.setBoxData(inputBoxData);
	solver.calculateTotalWidth();
	surfaceWidth = solver.getTotalWidth();
	
	std::cout << surfaceWidth << std::endl;
	
}
