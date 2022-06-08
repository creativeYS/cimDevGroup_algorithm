#include "StackCube.h"
#include "MapMaker.h"

int main()
{
    int depth, width;
    std::cin >> depth >> width;

    MapMaker map(depth, width);
    StackCube stackcube(map.getDepth(), map.getWidth(), map.inputCubeInfo());

    std::cout << stackcube.allSurfaceArea();
}