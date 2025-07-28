#ifndef BMP_READER_HPP
#define BMP_READER_HPP

#include <string>
#include <vector>
#include <cstdint>

#pragma pack(push,1)
struct BmpHeader {
    int16_t type{};         // 2
    int32_t fileSize{};     // 4
    int16_t reserved0{};    // 2
    int16_t reserved1{};    // 2
    int32_t offset{};       // 4
};
#pragma pack(pop)

#pragma pack(push,1)
struct BmpInfoHeader {
    int32_t headerSize{};           // 4
    int32_t width{};                // 4
    int32_t height{};               // 4
    int16_t colorPlanes{};          // 2
    int16_t bitsPerPixel{};         // 2
    int32_t compressionMethod{};    // 4
    int32_t imageSize{};            // 4
    int32_t horizontalResolution{}; // 4
    int32_t verticalResolution{};   // 4
    int32_t colorPalette{};         // 4
    int32_t importantColors{};      // 4
    int32_t redBitMask{};
    int32_t greenBitMask{};
    int32_t blueBitMask{};
    int32_t alphaBitMask{};
    int32_t colorSpace{};
    int32_t colorSpaceEndpoints[9]{};
    int32_t gammaRed{};
    int32_t gammaGreen{};
    int32_t gammaBlue{};
    int32_t intent{};
    int32_t profileData{};
    int32_t profileSize{};
    int32_t reserved{};
};
#pragma pack(pop)

class BmpReader {
    public:
        BmpReader(const std::string& filename);
        void readFromFile(const std::string& filename);
        void writeToFile(const std::string& filename);
        void writeToStdout();
        void drawLine(int x0, int y0, int x1, int y1);
        char* getPixel(int x, int y);
        void setPixel(int x, int y, int r, int g, int b);
        void invertPixel(int x, int y);
        void drawCross();
    private:
        BmpHeader header{};
        BmpInfoHeader infoHeader{};
        int rowSize{};
        int bytesPerPixel{};
        std::vector<char> data{};
};

#endif