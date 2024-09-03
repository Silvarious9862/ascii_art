#include "Bitmap.h"
#include "Luminance.h"
#include "MatrixIterator.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <format>


class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixMap;
class Bitmap;


void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix);
std::vector<std::vector<double>> CreateLightnessMatrix(Bitmap& image, std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> ChooseQuality(std::vector<std::vector<double>>& matrix_in, std::vector<std::vector<double>>& matrix_out, int quality);
std::vector<std::vector<char>>   LightnessToAscii(std::vector<std::vector<double>>& matrix);

void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix)
{
    int row_number = 1;
    for (int i = 0; i < matrix.size(); ) {
        for (int j = 0; j < matrix[i].size(); ) {
            std::cout << std::setw(2) << matrix[i][j];
            j++;
        }
        //std::cout << "\t\x1B[36mR\033[0m" << row_number << "\n";
        std::printf("\t\x1B[36mR%d\033[0m\n", row_number);
        row_number++; i++;
    }
};

std::vector<std::vector<double>> CreateLightnessMatrix(Bitmap& image, std::vector<std::vector<double>>& matrix)
{
    for (int row = 0; row < matrix.size(); ++row)           // for rows
    {
        for (int col = 0; col < matrix[row].size(); col++)  // for elements
        {
            const auto& pixel = image.GetPixel(row, col);    // get pixel
            const auto lightness = FindPerceivedLightness(pixel.GetRed(),    // find lightness of pixel
                pixel.GetGreen(),
                pixel.GetBlue());
            matrix.at(row).at(col) = lightness;             // set matrix of lightnesses
        }
    }
    return matrix;
}

std::vector<std::vector<double>> ChooseQuality(std::vector<std::vector<double>>& matrix_in, std::vector<std::vector<double>>& matrix_out, int quality = 5)
{

    if (quality < 0 || quality > 10) {
        throw std::exception("\x1B[36mQuality must be from 0 to 10\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
    }

    std::vector<double> row_one;
    double avg_lightness = 0;

    for (MatrixIterator mi(matrix_in, quality); !mi.CheckFullDone(); ) {
        avg_lightness = mi.CountAvg();
        row_one.emplace_back(avg_lightness);

        mi++;

        if (mi.CheckRowDone()) {
            matrix_out.emplace_back(row_one);
            row_one.clear();
            mi.UnsetRowDone();
        }
    }
    return matrix_out;
}

std::vector<std::vector<char>>LightnessToAscii(std::vector<std::vector<double>>&matrix)
{
    // string contains all ascii symbols that will be used in output image
    std::string ascii_string = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@"; 
    // volume contains precounted lighnesses for these symbols
    std::vector<double> ascii_volume = { 0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417,
        0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747,
        0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382,
        0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881,
        0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972,
        0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039,
        0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 1 };

    // output matrix
    std::vector<std::vector<char>> matrix_ascii(0, std::vector<char>(0, 0));

    for (int row = 0; row < matrix.size(); row++)   // for rows
    {
        std::vector<char> row_one_ascii;
        double current_pixel;
        for (int col = 0, pos = 0; col < matrix[row].size(); col++, pos = 0)    // for elems
        {
            current_pixel = matrix.at(row).at(col) / 100;       // normalization from 0..100 to 0..1
            while (current_pixel > ascii_volume[pos]) pos++;    // find position of needed character
            row_one_ascii.emplace_back(ascii_string[pos]);      // add character to row
        }
        row_one_ascii.shrink_to_fit();  // remove unused space in row
        matrix_ascii.emplace_back(row_one_ascii);   // add row to output matrix
    }
    return matrix_ascii;
}




int main()
{
    std::cout << "START" << std::endl;
    system("cls");
    std::string path = "samples/normal7.bmp";
    Bitmap image;           // create object of image

    try {
        if (!image.ReadBMP(path)) {    // read image from file.bmp
            throw std::exception("\x1B[33mCritical error\033[0m\t\t");
        }

        const auto& bitmapInfo = image.GetBitmapInfo(); // check for 24bits bmp, if not - reject
        if (bitmapInfo.GetBitcount() != 24) {
            throw std::exception("\x1B[31mIT'S NOT A 24-bit IMAGE!\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t");
        }


        // ------------- counting lightness -----------
        std::vector<std::vector<double>> matrix(bitmapInfo.GetHeight(), std::vector<double>(bitmapInfo.GetWidth(), 0));
        matrix = CreateLightnessMatrix(image, matrix);


        // ------------- average lightness by squares -------------
        std::vector<std::vector<double>> matrix_avg(0, std::vector<double>(0, 0));
        matrix_avg = ChooseQuality(matrix, matrix_avg);

         // ---------------- Change lightness to ascii ----------
        std::vector<std::vector<char>> matrix_ascii(0, std::vector<char>(0, 0));
        matrix_ascii = LightnessToAscii(matrix_avg);
        
        PrintMatrixAscii(matrix_ascii);
    }
    catch (std::out_of_range& e) 
    {
        std::cerr << "out_of_range: " << e.what() << '\n';
    }
    catch (std::exception& errtext)
    {
        std::cerr << errtext.what() << "\n";
    } 
    catch (const char* text) 
    {
        std::cerr << text << '\n';
    }
    catch (...) 
    {
        std::cerr << "unknown exception\n";
    }

    std::cout << "EXIT" << std::endl;
    return 0;
}
