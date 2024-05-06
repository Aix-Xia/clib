#include "../header/bmp.h"


uint32_t s_xpelspermeter = 0x0ec4;
uint32_t s_ypelspermeter = 0x0ec4;

RGB s_defaultColor(255, 255, 255);


int BitCountCorrect(uint16_t* bitCount) {
	if ((*bitCount != bitCount1) && (*bitCount != bitCount4) && (*bitCount != bitCount8) && (*bitCount != bitCount24) && (*bitCount != bitCount32)) {
		*bitCount = bitCount32;
	}
	return 0;
}
int SetPelsPerMeter(int32_t xPels, int32_t yPels) {
	s_xpelspermeter = xPels;
	s_ypelspermeter = yPels;
	return 0;
}
int SetPelsPerMeter(int32_t pels) {
	s_xpelspermeter = pels;
	s_ypelspermeter = pels;
	return 0;
}

int SetDefaultColor(uint8_t red, uint8_t green, uint8_t blue) {
	s_defaultColor.SetColor(red, green, blue);
	return 0;
}

RGB::RGB(uint8_t red, uint8_t green, uint8_t blue) {
	rgbBlue = blue;
	rgbGreen = green;
	rgbRed = red;
	rgbReserved = RESERVEDVALUE;
}
RGB::RGB(RGB& color) {
	rgbBlue = color.GetBlue();
	rgbGreen = color.GetGreen();
	rgbRed = color.GetRed();
	rgbReserved = color.GetReserved();
}
RGB::RGB() {
	rgbBlue = DEFAULTVALUE;
	rgbGreen = DEFAULTVALUE;
	rgbRed = DEFAULTVALUE;
	rgbReserved = RESERVEDVALUE;
}
RGB::~RGB() {

}
uint8_t RGB::GetRed() {
	return rgbRed;
}
uint8_t RGB::GetGreen() {
	return rgbGreen;
}
uint8_t RGB::GetBlue() {
	return rgbBlue;
}
uint8_t RGB::GetReserved() {
	return rgbReserved;
}
int RGB::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t reserved) {
	rgbBlue = blue;
	rgbGreen = green;
	rgbRed = red;
	rgbReserved = reserved;
	return 0;
}
int RGB::SetColor(RGB& color) {
	rgbBlue = color.GetBlue();
	rgbGreen = color.GetGreen();
	rgbRed = color.GetRed();
	rgbReserved = color.GetReserved();
	return 0;
}
int RGB::WriteRGB(FILE* fw) {
	fwrite(&rgbBlue, 1, 1, fw);
	fwrite(&rgbGreen, 1, 1, fw);
	fwrite(&rgbRed, 1, 1, fw);
	fwrite(&rgbReserved, 1, 1, fw);
	return 0;
}
int RGB::PrintColor() {
	printf("<class RGB>: { %d(r), %d(g), %d(b), %d(v) }\n", rgbRed, rgbGreen, rgbBlue, rgbReserved);
	return 0;
}


BMPFileHeader::BMPFileHeader(uint32_t fileSize, uint32_t offset) {
	bfType = FILETYPE;
	bfSize = fileSize;
	bfReserved1 = RESERVEDVALUE;
	bfReserved2 = RESERVEDVALUE;
	bfOffBits = offset;
}
BMPFileHeader::BMPFileHeader() {
	bfType = FILETYPE;
	bfSize = DEFAULTVALUE;
	bfReserved1 = RESERVEDVALUE;
	bfReserved2 = RESERVEDVALUE;
	bfOffBits = DEFAULTVALUE;
}
BMPFileHeader::~BMPFileHeader() {

}
int BMPFileHeader::SetFileHeader(uint32_t fileSize, uint32_t offset) {
	bfSize = fileSize;
	bfOffBits = offset;
	return 0;
}
int BMPFileHeader::WriteFileHeader(FILE* fw) {
	fwrite(&bfType, 1, 2, fw);
	fwrite(&bfSize, 1, 4, fw);
	fwrite(&bfReserved1, 1, 2, fw);
	fwrite(&bfReserved2, 1, 2, fw);
	fwrite(&bfOffBits, 1, 4, fw);
	return 0;
}
uint32_t BMPFileHeader::GetSize() {
	return bfSize;
}
uint32_t BMPFileHeader::GetOffBits() {
	return bfOffBits;
}



BMPInfoHeader::BMPInfoHeader(int32_t width, int32_t height, uint16_t bitCount) {
	BitCountCorrect(&bitCount);
	biSize = INFOSIZE;
	biWidth = width;
	biHeight = height;
	biPlanes = PLANEVALUE;
	biBitCount = bitCount;
	biCompression = 0;
	biSizeImage = ((width > 0 ? width : -width) * bitCount + 31) / 32 * 4 * (height > 0 ? height : -height);
	biXPelsPerMeter = s_xpelspermeter;
	biYPelsPerMeter = s_ypelspermeter;
	biClrUsed = 0;
	biClrImportant = 0;
}
BMPInfoHeader::BMPInfoHeader() {
	biSize = INFOSIZE;
	biWidth = DEFAULTVALUE;
	biHeight = DEFAULTVALUE;
	biPlanes = PLANEVALUE;
	biBitCount = 1;
	biCompression = 0;
	biSizeImage = DEFAULTVALUE;
	biXPelsPerMeter = s_xpelspermeter;
	biYPelsPerMeter = s_ypelspermeter;
	biClrUsed = 0;
	biClrImportant = 0;
}
BMPInfoHeader::~BMPInfoHeader() {

}
int BMPInfoHeader::SetInfoHeader(int32_t width, int32_t height, uint16_t bitCount) {
	BitCountCorrect(&bitCount);
	biWidth = width;
	biHeight = height;
	biBitCount = bitCount;
	biSizeImage = ((width > 0 ? width : -width) * bitCount + 31) / 32 * 4 * (height > 0 ? height : -height);
	return 0;
}
int BMPInfoHeader::WriteInfoHeader(FILE* fw) {
	fwrite(&biSize, 1, 4, fw);
	fwrite(&biWidth, 1, 4, fw);
	fwrite(&biHeight, 1, 4, fw);
	fwrite(&biPlanes, 1, 2, fw);
	fwrite(&biBitCount, 1, 2, fw);
	fwrite(&biCompression, 1, 4, fw);
	fwrite(&biSizeImage, 1, 4, fw);
	fwrite(&biXPelsPerMeter, 1, 4, fw);
	fwrite(&biYPelsPerMeter, 1, 4, fw);
	fwrite(&biClrUsed, 1, 4, fw);
	fwrite(&biClrImportant, 1, 4, fw);
	return 0;
}
uint32_t BMPInfoHeader::GetWidth() {
	return biWidth > 0 ? biWidth : -biWidth;
}
uint32_t BMPInfoHeader::GetHeight() {
	return biHeight > 0 ? biHeight : -biHeight;
}
uint16_t BMPInfoHeader::GetBitCount() {
	return biBitCount;
}



BMP::BMP(int32_t width, int32_t height, uint16_t bitCount) {
	BitCountCorrect(&bitCount);
	int colorCount = ((bitCount == bitCount24) || (bitCount == bitCount32)) ? 0 : (int)pow(2, bitCount);
	uint32_t fOffBits = 4 * colorCount + 14 + 40;
	uint32_t fSize = fOffBits + ((width > 0 ? width : -width) * bitCount + 31) / 32 * 4 * (height > 0 ? height : -height);
	fileHeader.SetFileHeader(fSize, fOffBits);
	infoHeader.SetInfoHeader(width, height, bitCount);

	rgb = (RGB*)calloc(colorCount, sizeof(RGB));
	data = (int*)calloc((width > 0 ? width : -width) * (height > 0 ? height : -height), sizeof(int));

	if (rgb == NULL || data == NULL) {
		perror("Error: calloc");
	}

	ResetColor();
	//for (int i = 0; i < colorCount; i++) {
	//	(rgb + i)->SetColor(255, 255, 255);
	//}
	ResetData();
	//for (int i = 0; i < (width > 0 ? width : -width) * (height > 0 ? height : -height); i++) {
	//	*(data + i) = 0;
	//}
}
BMP::~BMP() {
	free(rgb);
	free(data);
}
int BMP::SetColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
	int bitCount = infoHeader.GetBitCount();
	int colorCount = ((bitCount == bitCount24) || (bitCount == bitCount32)) ? 0 : (int)pow(2, bitCount);
	if (index >= colorCount) {
		perror("index is out of range!\n");
		return -1;
	}
	(rgb + index)->SetColor(red, green, blue);
	return 0;
}
int BMP::ResetColor() {
	int bitCount = infoHeader.GetBitCount();
	int colorCount = ((bitCount == bitCount24) || (bitCount == bitCount32)) ? 0 : (int)pow(2, bitCount);
	for (int i = 0; i < colorCount; i++) {
		(rgb + i)->SetColor(s_defaultColor);
	}
	return 0;
}
uint32_t BMP::GetDataIndex(uint32_t row, uint32_t col) {
	uint32_t ttWidth = infoHeader.GetWidth();
	uint32_t ttHeight = infoHeader.GetHeight();
	if ((col >= ttWidth) || (row >= ttHeight)) {
		perror("index is out of range!\n");
		return -1;
	}
	uint32_t index = row * ttWidth + col;
	return index;
}
int BMP::SetData(uint32_t row, uint32_t col, uint32_t value) {
	uint16_t bitCount = infoHeader.GetBitCount();
	if ((bitCount != 32) && (value > (uint32_t)(pow(2, bitCount) - 1))) {
		perror("value is out of range!\n");
		return -1;
	}
	uint32_t index = GetDataIndex(row, col);
	*(data + index) = value;

	return 0;
}
int BMP::ResetData() {
	uint32_t ttWidth = infoHeader.GetWidth();
	uint32_t ttHeight = infoHeader.GetHeight();
	uint32_t ttDataCount = ttWidth * ttHeight;
	for (uint32_t i = 0; i < ttDataCount; i++) {
		*(data + i) = 0;
	}
	return 0;
}
int BMP::Save(const char* fileName) {
	uint32_t ttHeight = infoHeader.GetHeight();
	uint32_t ttWidth = infoHeader.GetWidth();
	uint16_t bitCount = infoHeader.GetBitCount();
	int colorCount = ((bitCount == bitCount24) || (bitCount == bitCount32)) ? 0 : (int)pow(2, bitCount);

	FILE* fw = fopen(fileName, "wb");
	if (fw == NULL) {
		perror("bmp file create fail!");
		return 1;
	}

	// write fileHeader to fw
	fileHeader.WriteFileHeader(fw);

	// write infoHeader to fw
	infoHeader.WriteInfoHeader(fw);

	// write color to fw
	for (int i = 0; i < colorCount; i++) {
		(rgb + i)->WriteRGB(fw);
	}

	// write data in fw
	if (bitCount == bitCount32) {
		for (uint32_t height = 0; height < ttHeight; height++) {
			for (uint32_t width = 0; width < ttWidth; width++) {
				fwrite(data + height * ttWidth + width, 1, UNITBYTECNT, fw);
			}
		}
	}
	else if (bitCount == bitCount24) {
		uint32_t byteCntSupplement = (ttWidth * bitCount + 31) / 32 * 4 - 3 * ttWidth;

		uint8_t buffer;
		uint32_t data_t;
		for (uint32_t height = 0; height < ttHeight; height++) {
			for (uint32_t width = 0; width < ttWidth; width++) {
				data_t = *(data + height * ttWidth + width);
				for (int i = 0; i < 3; i++) {
					buffer = (uint8_t)(data_t & 0xff);
					fwrite(&buffer, 1, 1, fw);
					data_t = (data_t >> 8);
				}
			}
			for (uint32_t i = 0; i < byteCntSupplement; i++) {
				buffer = 0;
				fwrite(&buffer, 1, 1, fw);
			}
		}
	}
	else if (bitCount == bitCount8) {
		uint32_t byteCntSupplement = (ttWidth * bitCount + 31) / 32 * 4 - ttWidth;

		uint8_t buffer;
		uint32_t data_t;
		for (uint32_t height = 0; height < ttHeight; height++) {
			for (uint32_t width = 0; width < ttWidth; width++) {
				data_t = *(data + height * ttWidth + width);
				buffer = (uint8_t)(data_t & 0xff);
				fwrite(&buffer, 1, 1, fw);
			}
			for (uint32_t i = 0; i < byteCntSupplement; i++) {
				buffer = 0;
				fwrite(&buffer, 1, 1, fw);
			}
		}

	}
	else if (bitCount == bitCount4) {
		uint32_t byteCntFullByte = ttWidth / 2;
		uint32_t bitCntPartByte = ttWidth % 2;
		uint32_t byteCntSupplement = (ttWidth * bitCount + 31) / 32 * 4 - byteCntFullByte - (bitCntPartByte ? 1 : 0);

		uint8_t buffer;
		for (uint32_t height = 0; height < ttHeight; height++) {
			for (uint32_t grp = 0; grp < byteCntFullByte; grp++) {
				buffer = 0;
				for (int bit = 0; bit < 2; bit++) {
					buffer = (buffer << 4) + *(data + height * ttWidth + 2 * grp + bit);
				}
				fwrite(&buffer, 1, 1, fw);
			}
			if (bitCntPartByte != 0) {
				buffer = (uint8_t)((*(data + height * ttWidth + 2 * byteCntFullByte)) << 4);
				fwrite(&buffer, 1, 1, fw);
			}
			for (uint32_t i = 0; i < byteCntSupplement; i++) {
				buffer = 0;
				fwrite(&buffer, 1, 1, fw);
			}
		}
	}
	else if (bitCount == bitCount1) {
		uint32_t byteCntFullByte = ttWidth / 8;
		uint32_t bitCntPartByte = ttWidth % 8;
		uint32_t byteCntSupplement = (ttWidth * bitCount + 31) / 32 * 4 - byteCntFullByte - (bitCntPartByte ? 1 : 0);

		uint8_t buffer;
		for (uint32_t height = 0; height < ttHeight; height++) {
			for (uint32_t grp = 0; grp < byteCntFullByte; grp++) {
				buffer = 0;
				for (int bit = 0; bit < 8; bit++) {
					buffer = (buffer << 1) + *(data + height * ttWidth + 8 * grp + bit);
				}
				fwrite(&buffer, 1, 1, fw);
			}
			buffer = 0;
			for (uint32_t bit = 0; bit < bitCntPartByte; bit++) {
				buffer = (buffer << 1) + *(data + height * ttWidth + 8 * byteCntFullByte + bit);
			}
			buffer = buffer << (8 - bitCntPartByte);
			fwrite(&buffer, 1, 1, fw);
			for (uint32_t i = 0; i < byteCntSupplement; i++) {
				buffer = 0;
				fwrite(&buffer, 1, 1, fw);
			}
		}
	}
	else {
		return -1;
	}
	fclose(fw);
	return 0;
}