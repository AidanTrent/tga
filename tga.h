#ifndef TGA_H
#define TGA_H
#include <stdint.h>

typedef struct{
	uint8_t idLength;			// Length of image ID field (0-255)
	uint8_t colorMapType;		// If a color map is present (1) or not (0)
	uint8_t imageType;			// Compression and color types (0-3 and 9-11)
	uint16_t colorMapOrigin;	// Index of first color map entry
	uint16_t colorMapLength;	// Count of color map entries
	uint8_t colorMapEntrySize;	// Number of bits in each color map entry. 16 for Targa 16, 24 for Targa 24...
	uint16_t xOrigin;			// X coord of the lower left corner of the image
	uint16_t yOrigin;			// Y coord of the lower left corner of the image
	uint16_t width;				// Width of the image in pixels
	uint16_t height;			// Height of the image in pixels
	uint8_t imagePixelSize;		// Number of bits in a stored pixel index
	uint8_t imageDescriptorByte;// Document says to just keep this byte as 0
	uint8_t imageDataField[0];	// Array of image pixels.
	uint32_t dataFieldBytes;	// Number of bytes taken up by the imageDataField. Not saved when exporting
} TGAImg;

typedef struct{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} RGB;

TGAImg* makeImage(uint8_t idLength, uint8_t colorMapType,
						uint8_t imageType, uint16_t colorMapOrigin,
						uint16_t colorMapLength, uint8_t colorMapEntrySize,
						uint16_t xOrigin, uint16_t yOrigin,
						uint16_t width, uint16_t height,
						uint8_t imagePixelSize, uint8_t imageDescriptorByte);

void saveImage(char imageName[], TGAImg* img);

void setPixel(TGAImg* img, RGB color, int x, int y);
#endif
