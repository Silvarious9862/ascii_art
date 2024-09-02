#include "Bitmap.h"

Bitmap::Bitmap(const char* filename)
{
    bf.SetbfSize(bi);
    pixels.SetSize(bi.GetbiWidth(), bi.GetbiHeight());
    this->filename = filename;
}

void Bitmap::SetMonoBitmap(char red, char green, char blue)
{
    bi.SetbiBitCount(24);
    rgb.SetRGBtriple(red, green, blue);
    pixels.SetMonoArray(rgb);
}

void Bitmap::SaveAsBMP()
{
    std::fstream imageout("out.bmp", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
    try
    {
        if (!imageout.is_open()) throw "Cannot create file";
        imageout << bf << bi << pixels;
        if (imageout.fail()) throw "Cannot print in file";
        imageout.close();
        std::cout << "Saved successfully" << std::endl;
    }
    catch (char const* errorline)
    {
        std::cout << errorline << std::endl;
        imageout.close();
    }
}

int Bitmap::GetPixArrSize() { return bf.GetbfSize() - bf.GetbfOffBits(); }
int Bitmap::GetHeight() { return bi.GetbiHeight(); };
int Bitmap::GetbiWidth_public() { return bi.GetbiWidth(); };
int Bitmap::GetbiBitcount_public() { return bi.GetbiBitcount(); };

bool Bitmap::ReadBMP(const char* filename)
{
    this->filename = filename;
    std::fstream imagein(this->filename, std::ios_base::in | std::ios_base::binary);
    try {
        if (!imagein.is_open()) {
            throw "\x1B[31mCannot open to read file\033[0m\t\t";
        }
        
        imagein >> bf;
        if (!this->bf.CheckBM()) {
            throw "\x1B[31mFile is not a BMP or corrupted\033[0m\t\t";
        }

        imagein >> bi; 
        pixels.SetSize(bi.GetbiWidth(), bi.GetbiHeight());
        imagein >> pixels;

        imagein.close();
    }
    catch (char const* errorline)
    {
        std::cout << errorline << std::endl;
        imageout.close();
        return false;
    }
    return true;
}