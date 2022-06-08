#include<iostream>
#include<vector>

class BoxGroup 
{
private:
	std::vector<std::vector<int>> boxData;
	int surfaceWidth;

	int const sideWidthCalculator(int y, int x);
	bool isEdge(int y, int x) const;
	int getSideWidth(int y, int x, int my, int mx) const;
	int getEdgeSideWidth(int y, int x, bool targetFlag) const;
	bool isSafeRange(int my, int mx) const;

public:

	void setInitialData(const std::vector<std::vector<int>> inputBoxData);
	void surfaceWidthCalculator();
	int getSurfaceWidth() const;

};

// 데이터 주변을 -1로 채우면 엣지 디텍션이 편하지만... 메모리 낭비이지 않을까..?
void BoxGroup::setInitialData(const std::vector<std::vector<int>> inputBoxData){ boxData = inputBoxData; }

void BoxGroup::surfaceWidthCalculator() {
	int calcultatedSurface = 0;

	for (int i = 0; i < boxData.size(); i++) {
		for (int j = 0; j < boxData[0].size(); j++) {
			if (boxData[i][j] > 0) { // 한 칸에 박스가 존재할 경우
				calcultatedSurface += 2; // 위, 아랫면적 추가
				calcultatedSurface += sideWidthCalculator(i, j); // 옆면 면적 추가
			}
		}
	}
	surfaceWidth = calcultatedSurface;
}

int BoxGroup::getSideWidth(int y, int x, int my, int mx) const {
	
	if (boxData[my][mx] < boxData[y][x]) // 주변 박스의 높이가 나보다 낮다면
		return (boxData[y][x] - boxData[my][mx]); // 그 차이만큼 더해줌
	else return 0;

}

int BoxGroup::getEdgeSideWidth(int y, int x, bool indexIsY) const {
	int target = x;
	int len = boxData[0].size();
	if (indexIsY) { // 참인경우 -> y 순서
		target = y;
		len = boxData.size();	
	}
	if ((target == 0 || target == len - 1)) {
		if (target == 0 && target == len - 1)
			return 2 * boxData[y][x];
		else
			return boxData[y][x];
	}

	return 0;
}

bool BoxGroup::isSafeRange(int my, int mx) const{ // 범위 안전 확인
	if (my >= 0 && my < boxData.size() && mx >= 0 && mx < boxData[0].size()) return true;
	else return false;

}


int const BoxGroup::sideWidthCalculator(int y, int x) {

	int sideWidth = 0;
	int my[4] = { -1, 1, 0, 0, }; // 위 아래 왼쪽 오른쪽
	int mx[4] = { 0, 0, -1, 1 };

	if (!isEdge(y,x)) {
		for (int m = 0; m < 4; m++) {
			sideWidth += getSideWidth(y, x, y + my[m], x + mx[m]);
		}
	}
	else {
		sideWidth += getEdgeSideWidth(y, x, true);
		sideWidth += getEdgeSideWidth(y, x, false);

		for (int m = 0; m < 4; m++) {
			if (isSafeRange(y + my[m], x + mx[m])) {
				sideWidth += getSideWidth(y, x, y + my[m], x + mx[m]);
			}
		}
	}

	return sideWidth;

}

bool BoxGroup::isEdge(int y, int x) const {

	if (y > 0 && y < boxData.size()-1 && x > 0 && x < boxData[0].size()-1) return false;
	else return true;

}

int BoxGroup::getSurfaceWidth() const { return surfaceWidth;}


int main() {

	int rowNum = 0;
	int colNum = 0;
	int surfaceWidth = 0;

	std::cin >> rowNum >> colNum;
	std::vector<std::vector<int>> inputBoxData(rowNum, std::vector<int>(colNum, 0));

	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++)
			std::cin >> inputBoxData[i][j];
	}

	BoxGroup boxGroup{};

	boxGroup.setInitialData(inputBoxData);
	boxGroup.surfaceWidthCalculator();
	surfaceWidth = boxGroup.getSurfaceWidth();

	std::cout << surfaceWidth << std::endl;
	
}
