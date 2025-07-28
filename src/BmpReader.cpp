#include <iostream>
#include <fstream>

#include "BmpReader.hpp"

BmpReader::BmpReader(const std::string& filename) {
    readFromFile(filename);
}

void BmpReader::readFromFile(const std::string& filename) {
    std::ifstream ifs{};
    ifs.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    ifs.open(filename);

    ifs.read(reinterpret_cast<char*>(&header), sizeof(header));
    ifs.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    
    if (header.type != 0x4d42) {
        throw std::runtime_error("wrong file type");
    }
    
    if (infoHeader.bitsPerPixel != 24 && infoHeader.bitsPerPixel != 32) {
        throw std::runtime_error("unsupported pixel format");
    }

    extraData0.resize(header.offset - ifs.tellg());
    ifs.read(reinterpret_cast<char*>(extraData0.data()), extraData0.size());

    data.resize(infoHeader.imageSize);
    ifs.read(reinterpret_cast<char*>(data.data()), data.size());

    extraData1.resize(header.fileSize - ifs.tellg());
    ifs.read(reinterpret_cast<char*>(extraData1.data()), extraData1.size());

    ifs.close();

    rowSize = (infoHeader.bitsPerPixel * infoHeader.width / 32) * 4;
    bytesPerPixel = infoHeader.bitsPerPixel / 8;
}

void BmpReader::writeToFile(const std::string& filename) {
    std::ofstream ofs(filename);

    if (!ofs) {
        throw std::runtime_error("failed to open file");
    }

    ofs.write(reinterpret_cast<char*>(&header), sizeof(header));
    ofs.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    ofs.write(reinterpret_cast<char*>(extraData0.data()), extraData0.size());
    ofs.write(reinterpret_cast<char*>(data.data()), data.size());
    ofs.write(reinterpret_cast<char*>(extraData1.data()), extraData1.size());

    ofs.close();
}

void BmpReader::writeToStdout() {
    for (int i = infoHeader.height - 1; i >= 0; --i) {
        for (int j = 0; j < infoHeader.width; ++j) {
            if (data[i * rowSize + j * bytesPerPixel] == 0) {
                std::cout << '~';
            } else {
                std::cout << 'X';
            }
        }
        std::cout << '\n';
    }
}

unsigned char* BmpReader::getPixel(int x, int y) {
    return &data[x * rowSize + y * bytesPerPixel];
}

void BmpReader::setPixel(int x, int y, int r, int g, int b) {
    getPixel(x, y)[0] = r;
    getPixel(x, y)[1] = g;
    getPixel(x, y)[2] = b;
}

void BmpReader::invertPixel(int x, int y) {
    setPixel(y, x, 255 - getPixel(y, x)[0], 255 - getPixel(y, x)[1], 255 - getPixel(y, x)[2]);
}

void BmpReader::drawLine(int x0, int y0, int x1, int y1) {
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    } 
    if (x0>x1) { 
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            invertPixel(y, x);
        } else {
            invertPixel(x, y);
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        }
    } 
}

void BmpReader::drawCross() {
    drawLine(0, 0, infoHeader.width-1, infoHeader.height-1);
    drawLine(0, infoHeader.height-1, infoHeader.width-1, 0);
}