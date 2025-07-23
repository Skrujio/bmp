#include <iostream>
#include <string>

#include "BmpReader.hpp"

int main(int argc, char* argv[]) {
    std::string filename{};
    std::cout << "Enter input BMP file name: ";
    std::cin >> filename;
    
    try {
        BmpReader bmp(filename);
        bmp.writeToStdout();
        std::cout << '\n';
        bmp.drawCross();
        bmp.writeToStdout();
        std::cout << "Enter ouput BMP file name: ";
        std::cin >> filename;
        bmp.writeToFile(filename);
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
}