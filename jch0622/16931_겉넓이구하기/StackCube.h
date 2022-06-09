#pragma once

#include <vector>
#include <algorithm>

class StackCube
{
    typedef std::vector<std::vector<int> > cubeInfo;

private:
    const int depth;
    const int width;
    const cubeInfo map;

    StackCube();

    int getDepth() const;
    int getWidth() const;
    cubeInfo getMap() const;

    int eachSurfaceArea(const int & curDepth, const int & curWidth) const;

public:
    StackCube(const int & depth, const int & width, const cubeInfo & map);
    StackCube(const StackCube & src);
    ~StackCube();

    int allSurfaceArea() const;
};

StackCube::StackCube(const int & depth, const int & width, const cubeInfo & map) : depth(depth), width(width), map(map) {};
StackCube::StackCube(const StackCube & src) : depth(src.getDepth()), width(src.getWidth()), map(src.getMap()) {};
StackCube::~StackCube() {};

int StackCube::getDepth() const { return this->depth; };
int StackCube::getWidth() const { return this->width; };
std::vector<std::vector<int> > StackCube::getMap() const { return this->map; };

// function for algorithm
int StackCube::eachSurfaceArea(const int & curDepth, const int & curWidth) const
{
    std::vector<int> dx = {0, 1, 0, -1};
    std::vector<int> dy = {-1, 0, 1, 0};
    int area = 2;
    int curHeight = map[curDepth][curWidth];

    for (int idx = 0; idx < 4; idx++)
    {
        int aroundDepth = curDepth + dy[idx];
        int aroundWidth = curWidth + dx[idx];

        area += std::max(curHeight - map[aroundDepth][aroundWidth], 0);
    }
    return area;
}

int StackCube::allSurfaceArea() const
{
    int area = 0;
    
    for (int idxDepth = 1; idxDepth <= this->getDepth(); idxDepth++)
    {
        for (int idxWidth = 1; idxWidth <= this->getWidth(); idxWidth++)
        {
            area += eachSurfaceArea(idxDepth, idxWidth);
        }
    }
    return area;
}