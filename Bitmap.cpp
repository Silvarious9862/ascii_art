#include "Bitmap.h"

Bitmap::Bitmap(const char* filename)
{
    bf.SetbfSize(bi);
    pixels.SetArraySize(bi.GetbiHeight() * bi.GetbiWidth());
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
int Bitmap::GetbiHeight_public() { return bi.GetbiHeight(); };
int Bitmap::GetbiWidth_public() { return bi.GetbiWidth(); };
uint8_t Bitmap::GetPixelRed(int i)
{
    rgb = pixels.GetConcretePixel(i);
    return rgb.GetRgbRed();
}
uint8_t Bitmap::GetPixelGreen(int i)
{
    rgb = pixels.GetConcretePixel(i);
    return rgb.GetRgbGreen();
}
uint8_t Bitmap::GetPixelBlue(int i)
{
    rgb = pixels.GetConcretePixel(i);
    return rgb.GetRgbBlue();
}


void Bitmap::ReadBMP(const char* filename)
{
    this->filename = filename;
    std::fstream imagein(this->filename, std::ios_base::in | std::ios_base::binary);
    try {
        if (!imagein.is_open()) throw "Cannot open to read file";
        imagein >> bf;
        if (!this->bf.CheckBM()) throw "File is not a BMP or corrupted";
        pixels.SetArraySize(GetPixArrSize());
        imagein >> bi >> pixels;
        if (imagein.eofbit) throw "Readed successfully";
        imagein.close();
    }
    catch (char const* errorline)
    {
        std::cout << errorline << std::endl;
        imageout.close();
    }
}