#include "Bitmap.h"
#include "Luminance.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

class BitmapFileHeader;
class BitmapInfoHeader;
class Pallette;
class RGBtriple;
class PixMap;
class Bitmap;


void PrintMatrix_skip10(std::vector<std::vector <double>> const& matrix);
void PrintMatrixAvg(std::vector<std::vector <double>> const& matrix);
void PrintMatrixAscii(std::vector<std::vector <char>> const& matrix);


void PrintMatrix_skip10(std::vector<std::vector <double>> const& matrix)
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

void PrintMatrixAvg(std::vector<std::vector <double>> const& matrix)
{
    int row_number = 1;
    for (int i = 0; i < matrix.size(); ) {
        for (int j = 0; j < matrix[i].size(); ) {
            std::cout << std::setw(3) << std::setprecision(2) << matrix[i][j] << " ";
            j++;
        }
        std::cout << "\t\x1B[31mR\033[0m" << row_number << std::endl;
        row_number++; i++;
    }
};

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

int main()
{
    std::cout << "START" << std::endl;
    Bitmap image;

    try {
        if (!image.ReadBMP("samples/normal7.bmp")) throw std::exception("\x1B[33mCritical error\033[0m\t\t");
        
        const auto& bitmapInfo = image.GetBitmapInfo();
        if (bitmapInfo.GetbiBitcount() != 24) {
            throw "\x1B[31mIT'S NOT A 24-bit IMAGE!\033[0m\t\t\n\x1B[33mCritical error\033[0m\t\t";
        }


        // ------------- считаем все €ркости -----------
        std::vector<std::vector<double>> matrix(bitmapInfo.GetbiHeight(), std::vector<double>(bitmapInfo.GetbiWidth(), 0));
        {
            for (int row = 0; row < matrix.size(); ++row)
            {
                for (int col = 0; col < matrix[row].size(); col++)
                {
                    const auto& pixel = image.GetPixel(row, col);
                    const auto lightness = FindPerceivedLightness(pixel.GetRgbRed(), 
                                                                  pixel.GetRgbGreen(), 
                                                                  pixel.GetRgbBlue());
                    matrix.at(row).at(col) = lightness;
                }
            }
        }
        // PrintMatrix_skip10(matrix);


        // MatrixIterator mi(width, height); // calls reset inside
        // mi.reset(); // resets current position
        // mi.isDone(); // true - can move to the next item, otherwise - false
        // auto currPos = mi.currentPosition(); // return current position
        // auto newCurrPos = mi.next(); // can return currentPosition
        // auto xInfo = currPos.getX();
        // for (auto i = xInfo.begin(); i < xInfo.end(); ++i) // xInfo usage

        // auto el = seits.getElList()
        // el.getParams();

#define PRECISION 3
    // ------------ считаем средние €ркости по квадратам -------------
        std::vector<std::vector<double>> matrix_avg(0, std::vector<double>(0, 0));
        double avg_lightness = 0;

        for (int row = PRECISION / 2, row_avg = 0; row < matrix.size(); row += PRECISION, row_avg++)
        {
            std::vector<double> row_one;
            for (int col = PRECISION / 2; col < matrix[row].size(); col += PRECISION)
            {
                if (col == matrix[row].size() - 1) col--;
                if (row == matrix.size() - 1) row--;
                avg_lightness = matrix.at(row - 1).at(col - 1);
                avg_lightness += matrix.at(row - 1).at(col);
                avg_lightness += matrix.at(row - 1).at(col + 1);
                avg_lightness += matrix.at(row).at(col - 1);
                avg_lightness += matrix.at(row).at(col);
                avg_lightness += matrix.at(row).at(col + 1);
                avg_lightness += matrix.at(row + 1).at(col - 1);
                avg_lightness += matrix.at(row + 1).at(col);
                avg_lightness += matrix.at(row + 1).at(col + 1);
                avg_lightness /= pow(PRECISION, 2);
                row_one.push_back(avg_lightness);
            }
            matrix_avg.push_back(row_one);
        }

        // PrintMatrixAvg(matrix_avg);

         // ---------------- заменить €ркость на ascii ----------
        std::string ascii_string = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
        std::vector<double> ascii_volume = { 0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417,
            0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747,
            0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382,
            0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881,
            0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972,
            0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039,
            0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999 };

        std::vector<std::vector<char>> matrix_ascii(0, std::vector<char>(0, 0));

        for (int row = 0; row < matrix_avg.size(); row++)
        {
            std::vector<char> row_one_ascii;
            double current_pixel;
            for (int col = 0, pos = 0; col < matrix_avg[row].size(); col++, pos = 0)
            {
                current_pixel = matrix_avg.at(row).at(col) / 100;
                while (current_pixel > ascii_volume[pos]) pos++;
                row_one_ascii.emplace_back(ascii_string[pos]);
            }
            row_one_ascii.shrink_to_fit();
            matrix_ascii.emplace_back(row_one_ascii);
        }

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
