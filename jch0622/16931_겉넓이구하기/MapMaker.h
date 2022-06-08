#pragma once
#include <iostream>
#include <vector>

class MapMaker
{
    typedef std::vector<std::vector<int> > cubeInfo;

private:
    int depth;
    int width;

    MapMaker();

public:
    MapMaker(const int & depth, const int & width);
    MapMaker(const MapMaker & src);
    ~MapMaker();

    int getDepth() const;
    int getWidth() const;

    cubeInfo inputCubeInfo() const;

    MapMaker & operator=(const MapMaker & rhs);

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

// function for algorithm
std::vector<std::vector<int> > MapMaker::inputCubeInfo() const
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