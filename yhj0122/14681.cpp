#include<iostream>
#include<vector>

using namespace std;

class Axis
{
private:
    pair<int, int> dot;
    
public:
    void setDotPosition(pair<int, int>);
    int findQuadrant();
    int result = 0;
};

void Axis::setDotPosition(pair<int, int> inputData){ dot = inputData; }

int Axis::findQuadrant(){
    
    if(dot.first > 0 && dot.second > 0) result = 1;
    else if (dot.first < 0 && dot.second > 0) result = 2;
    else if (dot.first < 0 && dot.second < 0) result = 3;
    else result = 4;
    
    return result;
}

class Helper
{
private:
    pair<int, int> inputData;
public:
    int temInputX;
    int temInputY;
    void setInputData();
    pair<int, int> getInputDate();
};

void Helper::setInputData(){ // 데이터 입력 형식이 변화할 경우 이곳 에서 대응하여 int pair 형태로 만 들 수 있음
    cin >> temInputX;
    cin >> temInputY;
    
    inputData.first = temInputX;
    inputData.second = temInputY;
}

pair<int,int> Helper::getInputDate(){ return inputData; }


int main(){
    
    int result = 0;
    Helper helper;
    Axis axis;
    
    helper.setInputData();
    axis.setDotPosition(helper.getInputDate());
    result = axis.findQuadrant();
    
    cout<<result<<endl;
}
