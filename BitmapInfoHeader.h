#pragma once
#include <cstdint>
#include <iostream>

class BitmapInfoHeader
{
private:
    uint32_t biSize;
    uint32_t biWidth, biHeight;
    uint16_t biPlanes, biBitCount;
    uint32_t biCompression, biSizeImage;
    uint32_t biXPelsPerMeter, biYPelsPerMeter;
    uint32_t biClrUsed, biClrImportant;

public:
    BitmapInfoHeader();
    uint32_t GetbiWidth() const;
    uint32_t GetbiHeight() const;
    void SetbiBitCount(int bitCount = 24);
    friend std::ostream& operator<< (std::ostream& outstream, const BitmapInfoHeader& bi);
    friend std::istream& operator>> (std::istream& instream, BitmapInfoHeader& bi);
};

