#include "RGBtriple.h"

RGBtriple::RGBtriple() { rgbBlue = 0; rgbGreen = 0; rgbRed = 0; };

void RGBtriple::SetRGBtriple(uint8_t red, uint8_t green, uint8_t blue)
{
    rgbBlue = blue;
    rgbGreen = green;
    rgbRed = red;
}

void RGBtriple::SetRGBblue(uint8_t blue) { rgbBlue = blue; }
void RGBtriple::SetRGBgreen(uint8_t green) { rgbGreen = green; }
void RGBtriple::SetRGBred(uint8_t red) { rgbRed = red; }
uint8_t RGBtriple::GetRgbBlue() const { return rgbBlue; }
uint8_t RGBtriple::GetRgbGreen() const { return rgbGreen; }
uint8_t RGBtriple::GetRgbRed() const { return rgbRed; }

std::ostream& operator<< (std::ostream& outstream, const RGBtriple& rgb)
{
    return outstream << rgb.rgbBlue << rgb.rgbGreen << rgb.rgbRed;
}
std::istream& operator>> (std::istream& instream, const RGBtriple& rgb)
{
    instream.read((char*)rgb.rgbBlue, sizeof(rgb.rgbBlue));
    instream.read((char*)rgb.rgbGreen, sizeof(rgb.rgbGreen));
    instream.read((char*)rgb.rgbRed, sizeof(rgb.rgbRed));
    return instream;
}