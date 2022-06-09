#include <iostream>
#include "StackCube.h"

int main()
{
    typedef std::vector<std::vector<int> > cubeInfo;

    int depth, width;
    std::cin >> depth >> width;

    cubeInfo map(depth + 2, std::vector<int>(width + 2, 0));

    for (int idxDepth = 1; idxDepth <= depth; idxDepth++)
    {
        for (int idxWidth = 1; idxWidth <= width; idxWidth++)
        {
            std::cin >> map[idxDepth][idxWidth];
        }
    }

    StackCube stackcube(depth, width, map);
    std::cout << stackcube.allSurfaceArea();
}