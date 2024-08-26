#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "Bitmap.h"

class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixArray;
class Bitmap;

double FindPerceivedLightness(uint8_t red, uint8_t green, uint8_t blue);
inline double LumiToLstar(double luminance);
inline double ColorLinear(double color);
void PrintMatrix(std::vector<double> const& matrix, int row_size);
void PrintMatrix2(std::vector<std::vector <double>> const& matrix2);

double FindPerceivedLightness(uint8_t red, uint8_t green, uint8_t blue)
{
    double colorRed = red / 255.0, colorGreen = green / 255.0, colorBlue = blue / 255.0;
    return LumiToLstar(ColorLinear(colorRed) * 0.2126 + ColorLinear(colorGreen) * 0.7152 + ColorLinear(colorBlue) * 0.0722);
}

inline double LumiToLstar(double luminance)
{
    if (luminance <= 216 / 24389) return luminance * 903.3;
    else return pow(luminance, (1.0 / 3.0)) * 116.0 - 16.0;
}

inline double ColorLinear(double color)
{
    if (color <= 0.4045) return color / 12.92;
    else return pow(((color + 0.055) / 1.055), 2.4);
}

void PrintMatrix(std::vector<double> const& matrix, int row_size)
{
    int row_number = 1;
    for (int i = matrix.size() - 1, j = 0; i >= 0;)
    {
        std::cout << std::setw(4) << std::setprecision(2) << matrix[i] << " ";
        i -= 10; j += 10;
        if (j >= row_size) { std::cout << "  R" << row_number << std::endl; j = 0; row_number++; }
    }
};

void PrintMatrix2(std::vector<std::vector <double>> const& matrix2)
{
    int row_number = 1;
    for (int i = 0; i < matrix2.size(); ) {
        for (int j = 0; j < matrix2[i].size(); ) {
            std::cout << std::setw(3) << std::setprecision(2) << matrix2[i][j] << " ";
            j += 10;
        }
        std::cout << " R" << row_number << std::endl;
        row_number++; i += 10;
    }
};

int main()
{
    std::cout << "START" << std::endl;
    Bitmap image;

    image.ReadBMP("samples/in.bmp");

    const int width = image.GetbiWidth_public(), height = image.GetbiHeight_public();

    uint8_t red, green, blue;
    double lightness;
    std::vector<std::vector<double>> matrix2(width, std::vector<double>(height, 0));

    for (int i = matrix2.size() - 1, k = 0; i << matrix2.size() >= 0; i--)
    {
        for (int j = 0; j < matrix2[i].size(); j++)
        {
            red = image.GetPixelRed(k);
            green = image.GetPixelGreen(k);
            blue = image.GetPixelBlue(k);
            lightness = FindPerceivedLightness(red, green, blue);
            matrix2.at(i).at(j) = lightness;
            k++;
        }
    }
    PrintMatrix2(matrix2);


    /*std::vector<double> matrix(1, 0);    
    matrix.resize(image.GetPixArrSize() / 3);


    for (int i = 0; i < matrix.size(); i++)
    {
        red = image.GetPixelRed(i);
        green = image.GetPixelGreen(i);
        blue = image.GetPixelBlue(i);
        lightness = FindPerceivedLightness(red, green, blue);
        matrix.at(i) = lightness;
    }
    PrintMatrix(matrix, image.GetbiWidth_public());*/

    std::cout << "EXIT" << std::endl;
    return 0;
}
