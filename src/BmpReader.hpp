#ifndef BMP_READER_HPP
#define BMP_READER_HPP

#include <string>
#include <vector>

struct BmpHeader {
    int type{};         // 2
    int fileSize{};     // 4
    int reserved0{};    // 2
    int reserved1{};    // 2
    int offset{};       // 4
};

struct BmpInfoHeader {
    int headerSize{};           // 4
    int width{};                // 4
    int height{};               // 4
    int colorPlanes{};          // 2
    int bitsPerPixel{};         // 2
    int compressionMethod{};    // 4
    int imageSize{};            // 4
    int horizontalResolution{}; // 4
    int verticalResolution{};   // 4
    int colorPalette{};         // 4
    int importantColors{};      // 4
};

class BmpReader {
    public:
        BmpReader(const std::string& filename);
        void readFromFile(const std::string& filename);
        void writeToFile(const std::string& filename);
        void writeToStdout();
        void drawLine(int x0, int y0, int x1, int y1);
        unsigned char* getPixel(int x, int y);
        void setPixel(int x, int y, int r, int g, int b);
        void invertPixel(int x, int y);
        void drawCross();
    private:
        int rowSize{};
        int bytesPerPixel{};
        BmpHeader header{};
        BmpInfoHeader infoHeader{};
        std::vector<unsigned char> extraData0{};
        std::vector<unsigned char> data{};
        std::vector<unsigned char> extraData1{};
};

#endif