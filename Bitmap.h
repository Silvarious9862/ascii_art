#pragma once
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Pallette.h"
#include "PixArray.h"
#include <fstream>
#include <string>
#include <iostream>

class Bitmap
{
private:
    BitmapInfoHeader bi;
    BitmapFileHeader bf;
    Pallette pal;
    RGBtriple rgb;
    PixMap pixels;
    std::fstream imageout;
    std::string filename;

public:

    Bitmap(const char* filename = "tmp.bmp");
    void SetMonoBitmap(char red, char green, char blue);
    void SaveAsBMP();
    int GetPixArrSize();
    const BitmapInfoHeader& GetBitmapInfo() const { return bi; }
    
    const RGBtriple& GetPixel(int row, int col) 
    { 
        return pixels.GetPixel(row, col); 
    }

    bool ReadBMP(std::string filename);
};

