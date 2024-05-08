#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULTVALUE	0

#define FILETYPE		0x4d42
#define RESERVEDVALUE	0

#define INFOSIZE		40
#define PLANEVALUE		1


#define bitCount1		((uint16_t)1)
#define bitCount4		((uint16_t)4)
#define bitCount8		((uint16_t)8)
#define bitCount24		((uint16_t)24)
#define bitCount32		((uint16_t)32)

#define BITCNTINBYTE	8
#define UNITBYTECNT		4


extern int BitCountCorrect(uint16_t* bitCount);
extern int SetPelsPerMeter(int32_t xPels, int32_t yPels);
extern int SetPelsPerMeter(int32_t pels);

extern int SetDefaultColor(uint8_t red, uint8_t green, uint8_t blue);


class RGB {
public:
	RGB(uint8_t red, uint8_t green, uint8_t blue);
	RGB(RGB& color);
	RGB();
	~RGB();
	uint8_t GetRed();
	uint8_t GetGreen();
	uint8_t GetBlue();
	uint8_t GetReserved();
	int SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t reserved = RESERVEDVALUE);
	int SetColor(RGB& color);
	int WriteRGB(FILE* fw);
	int PrintColor();
private:
	uint8_t rgbBlue;
	uint8_t rgbGreen;
	uint8_t rgbRed;
	uint8_t rgbReserved;
};


class BMPFileHeader {
public:
	BMPFileHeader(uint32_t fileSize, uint32_t offset);
	BMPFileHeader();
	~BMPFileHeader();
	int SetFileHeader(uint32_t fileSize, uint32_t offset);
	int WriteFileHeader(FILE* fw);
	uint32_t GetSize();
	uint32_t GetOffBits();
private:
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};


class BMPInfoHeader {
public:
	BMPInfoHeader(int32_t width, int32_t height, uint16_t bitCount);
	BMPInfoHeader();
	~BMPInfoHeader();
	int SetInfoHeader(int32_t width, int32_t height, uint16_t bitCount);
	int WriteInfoHeader(FILE* fw);
	uint32_t GetWidth();
	uint32_t GetHeight();
	uint16_t GetBitCount();
private:
	uint32_t biSize;
	int32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};


class BMP {
public:
	BMP(int32_t width, int32_t height, uint16_t bitCount);
	~BMP();
	int SetColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
	int ResetColor();
	uint32_t GetDataIndex(uint32_t row, uint32_t col);
	int SetData(uint32_t row, uint32_t col, uint32_t value);
	int ResetData();
	int Save(const char* fileName);
private:
	BMPFileHeader fileHeader;
	BMPInfoHeader infoHeader;
	RGB* rgb;
	int* data;
};
