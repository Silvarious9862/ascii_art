#pragma once
#include "RGBtriple.h"
#include <cstdint>
#include <iostream>
#include <vector>

class PixArray
{
private:
    std::vector<RGBtriple> pixelArray;

public:

    void SetArraySize(int i);
    void SetMonoArray(RGBtriple triple);
    void SetConcretePixel(int i, RGBtriple triple);
    void SetConcretePixel(int i, char blue, char green, char red);
    RGBtriple GetConcretePixel(int i);
    friend std::ostream& operator<< (std::ostream& outstream, PixArray& pixels);
    friend std::istream& operator>> (std::istream& instream, PixArray& pixels);
};

