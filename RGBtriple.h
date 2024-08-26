#pragma once
#include <cstdint>
#include <iostream>

class RGBtriple
{
private:
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;

public:
    RGBtriple();
    void SetRGBtriple(uint8_t red, uint8_t green, uint8_t blue);
    void SetRGBblue(uint8_t blue);
    void SetRGBgreen(uint8_t green);
    void SetRGBred(uint8_t red);
    uint8_t GetRgbBlue() const;
    uint8_t GetRgbGreen() const;
    uint8_t GetRgbRed() const;
    friend std::ostream& operator<< (std::ostream& outstream, const RGBtriple& rgb);
    friend std::istream& operator>> (std::istream& instream, const RGBtriple& rgb);
};

