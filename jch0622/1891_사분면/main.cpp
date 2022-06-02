#include "FragmentQuadrant.h"
#include <iostream>

int main()
{
    int     digit;
    string  number;
    cin >> digit >> number;
    FragmentQuadrant    fragmentQuadrant(digit, number);

    long long x, y;
    cin >> x >> y;
    fragmentQuadrant.moveXY(x, y);
    cout << fragmentQuadrant.getNumber() << endl;
}