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

class Highway
{
private:
	Highway();
	int highwayLen;
	int numOfShortcut;

public:
	Highway(int len, int num) { setHighway(len, num);  };
	int getHighwayLen();
	int getNumOfShortcut();
	void setHighway(int len, int num);
};

int Highway::getHighwayLen() { return  highwayLen; }
int Highway::getNumOfShortcut() { return numOfShortcut; }
void Highway::setHighway(int len, int num) {
	highwayLen = len;
	numOfShortcut = num;
}

class Shortcut
{
private:
	int destination;
	int cost;
public:
	int getDestination();
	int getCost();
	void setShorcut(int des, int cos);
};

int Shortcut::getDestination() { return destination; }
int Shortcut::getCost() { return cost; }
void Shortcut::setShorcut(int des, int cos) {
	destination = des;
	cost = cos;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int numShorcut, lenHighway;
	int beforeDistance = -1; // i==0 일때 distance를 0으로 만들기 위해 초기값 설정

	cin >> numShorcut >> lenHighway;

	vector<int> distance(lenHighway + 1, INT_MAX);
	distance[lenHighway] = lenHighway;
	
	Highway highway(lenHighway, numShorcut);

	// 같은 위치의 출발/도착이면서 cost가 다른 경우가 있기 때문에 이중벡터 사용
	vector<vector<Shortcut>> shortcutData(highway.getHighwayLen() + 1, vector<Shortcut>());

	for (int i = 0; i < highway.getNumOfShortcut(); i++) {

		int start, departure, cost;
		cin >> start >> departure >> cost;

		// 말이 안되는 경우는 데이터에서 제외
		if ((departure - start) <= cost || departure > highway.getHighwayLen()) {
			continue;
		}

		Shortcut temShortcut;

		temShortcut.setShorcut(departure, cost);
		shortcutData[start].push_back(temShortcut);
	}

	for (int i = 0; i <= highway.getHighwayLen(); i++) {
		// 전 위치의 데이터 설정
		if (i > 0) {
			beforeDistance = distance[i - 1];
		}

		distance[i] = min(distance[i], beforeDistance + 1);

		for (auto next : shortcutData[i]) {
			if (distance[i] + next.getCost() < distance[next.getDestination()]) {
				distance[next.getDestination()] = distance[i] + next.getCost();
			}
		}

	}

	cout << distance[highway.getHighwayLen()] << endl;
}
