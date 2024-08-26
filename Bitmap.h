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
    PixArray pixels;
    std::fstream imageout;
    std::string filename;

public:

    Bitmap(const char* filename = "tmp.bmp");
    void SetMonoBitmap(char red, char green, char blue);
    void SaveAsBMP();
    int GetPixArrSize();
    int GetbiHeight_public();
    int GetbiWidth_public();
    uint8_t GetPixelRed(int i);
    uint8_t GetPixelGreen(int i);
    uint8_t GetPixelBlue(int i);
    void ReadBMP(const char* filename);
};

