#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "Bitmap.h"
#include "Luminance.h"

class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixArray;
class Bitmap;



void PrintMatrix(std::vector<std::vector <double>> const& matrix)
{
    int row_number = 1;
    for (int i = 0; i < matrix.size(); ) {
        for (int j = 0; j < matrix[i].size(); ) {
            std::cout << std::setw(3) << std::setprecision(2) << matrix[i][j] << " ";
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
    PrintMatrix(matrix2);

    std::cout << "EXIT" << std::endl;
    return 0;
}
