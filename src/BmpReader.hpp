#ifndef BMP_READER_HPP
#define BMP_READER_HPP

#include <string>
#include <vector>
#include <cstdint>

#pragma pack(push,1)
struct BmpHeader {
    int16_t type{};
    int32_t fileSize{};
    int16_t reserved0{};
    int16_t reserved1{};
    int32_t offset{};
};
#pragma pack(pop)

#pragma pack(push,1)
struct BmpInfoHeader {
    int32_t headerSize{};
    int32_t width{};
    int32_t height{};
    int16_t colorPlanes{};
    int16_t bitsPerPixel{};
    int32_t compressionMethod{};
    int32_t imageSize{};
    int32_t horizontalResolution{};
    int32_t verticalResolution{};
    int32_t colorPalette{};
    int32_t importantColors{};
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