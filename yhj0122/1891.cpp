#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#include<cmath>
#include<bitset>
#include<map>
#include<climits>

using namespace std;

class Helper
{
private:
	pair<int, int> curPosition;
public:
	pair<int,int> numToAxis(vector<vector<int>> map, int dot); // 숫자를 행열인덱스로 변환
	int AxisToNum(pair<int, int>); // 행렬인덱스를 숫자로 변환
	pair<int, int> shifter(pair<int, int> position, int mx, int my); // 행렬인덱스 쉬프팅
};




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int d, dot, mx, my, result;
	
	vector<vector<int>> map(pow(2, d), vector<int>()); // d를 바탕으로 2차원 백터를 만들어 dot 위치를 특정함
	Helper helper;

	cin >> d;
	cin >> dot;

	pair<int, int> position;
	position = helper.numToAxis(map, dot);
	position = helper.shifter(position, mx, my);
	result = helper.AxisToNum(position);

	cout << result << endl;
}
