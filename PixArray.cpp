#include "PixArray.h"

void PixArray::SetArraySize(int i)
{
    RGBtriple rgb_null;
    pixelArray.resize(i, rgb_null);
}

void PixArray::SetMonoArray(RGBtriple triple)
{
    for (int i = 0; i < pixelArray.size(); i++)
    {
        pixelArray.at(i) = triple;
    }
    pixelArray.shrink_to_fit();
}

void PixArray::SetConcretePixel(int i, RGBtriple triple)
{
    pixelArray[i] = triple;
}

void PixArray::SetConcretePixel(int i, char blue, char green, char red)
{
    pixelArray[i].SetRGBtriple(red, green, blue);
    RGBtriple triple = GetConcretePixel(i);
    pixelArray.at(i) = triple;
}

RGBtriple PixArray::GetConcretePixel(int i)
{
    return pixelArray.at(i);
}

std::ostream& operator<< (std::ostream& outstream, PixArray& pixels)
{
    for (int i = 0; i < pixels.pixelArray.size(); i++)
    {
        outstream << pixels.GetConcretePixel(i);
    }
    return outstream;
}

std::istream& operator>> (std::istream& instream, PixArray& pixels)
{
    char tmpblue, tmpgreen, tmpred;
    for (int i = 0; i < pixels.pixelArray.size(); i++)
    {
        instream.read((char*)&tmpblue, sizeof(tmpblue));
        pixels.pixelArray[i].SetRGBblue(tmpblue);
        instream.read((char*)&tmpgreen, sizeof(tmpgreen));
        pixels.pixelArray[i].SetRGBgreen(tmpgreen);
        instream.read((char*)&tmpred, sizeof(tmpred));
        pixels.pixelArray[i].SetRGBred(tmpred);
    }
    return instream;
}