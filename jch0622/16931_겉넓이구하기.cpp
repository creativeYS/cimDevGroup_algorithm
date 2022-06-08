#include <iostream>
#include <vector>
#include <algorithm>

class StackCube
{
    typedef std::vector<std::vector<int> > cubeInfo;
private:
    int depth;
    int width;
    cubeInfo map;

    StackCube();

    int eachSurfaceArea(const int & curDepth, const int & curWidth) const;

    int getDepth() const;
    int getWidth() const;
    cubeInfo getMap() const;

public:
    StackCube(const int & depth, const int & width, const cubeInfo & map);
    StackCube(const StackCube & src);
    ~StackCube();

    StackCube & operator=(const StackCube & rhs);

    int allSurfaceArea() const;
};

/* StackCube */

// constructor
StackCube::StackCube()
: depth(0), width(0), map(0, std::vector<int>(0, 0)) {};

StackCube::StackCube(const int & depth, const int & width, const cubeInfo & map)
: depth(depth), width(width), map(map) {};

StackCube::StackCube(const StackCube & src)
: depth(src.getDepth()), width(src.getWidth()), map(src.getMap()) {};

// destructor
StackCube::~StackCube() {};

// getter function
int StackCube::getDepth() const { return this->depth; };
int StackCube::getWidth() const { return this->width; };
std::vector<std::vector<int> > StackCube::getMap() const { return this->map; };

// assignment operator
StackCube & StackCube::operator=(const StackCube & rhs)
{
    this->depth = rhs.getDepth();
    this->width = rhs.getWidth();
    this->map = rhs.getMap();
    return *this;
}

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

class MapMaker
{
    typedef std::vector<std::vector<int> > cubeInfo;
private:
    int depth;
    int width;

    MapMaker();
    int getDepth() const;
    int getWidth() const;

public:
    MapMaker(const int & depth, const int & width);
    MapMaker(const MapMaker & src);
    ~MapMaker();

    MapMaker & operator=(const MapMaker & rhs);
    cubeInfo makeCubeInfo() const;
};

MapMaker::MapMaker() : depth(0), width(0) {};
MapMaker::MapMaker(const int & depth, const int & width) : depth(depth), width(width) {};
MapMaker::MapMaker(const MapMaker & src) : depth(src.getDepth()), width(src.getWidth()) {};
MapMaker::~MapMaker() {};

int MapMaker::getDepth() const { return this->depth; };
int MapMaker::getWidth() const { return this->width; };

MapMaker & MapMaker::operator=(const MapMaker & rhs)
{
    this->depth = rhs.getDepth();
    this->width = rhs.getWidth();
    return *this;
}

std::vector<std::vector<int> > MapMaker::makeCubeInfo() const
{
    cubeInfo map(depth + 2, std::vector<int>(width + 2, 0));
    for (int idxDepth = 1; idxDepth <= this->getDepth(); idxDepth++)
    {
        for (int idxWidth = 1; idxWidth <= this->getWidth(); idxWidth++)
        {
            std::cin >> map[idxDepth][idxWidth];
        }
    }
    return map;
}



int main()
{
    int depth, width;
    std::cin >> depth >> width;

    MapMaker map(depth, width);
    StackCube stackcube(depth, width, map.makeCubeInfo());
    
    std::cout << stackcube.allSurfaceArea();
}

// https://www.onlinegdb.com/online_c++_compiler