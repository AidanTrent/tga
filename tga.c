/* Aidan Trent
 * An implementation of 24 bit TARGA image (create, manipulate pixels, and export)
 * Put together with a elementary understanding of C
 * Made with info from https://www.gamers.org/dengine/quake3/TGA.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEADER_BYTES 18 // Ammount of bytes header will take up

#pragma pack(1)
typedef struct {
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
	uint8_t imageDataField[];	// Array of image pixels.
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
						uint8_t imagePixelSize, uint8_t imageDescriptorByte){
	// Allocate memory for header + image pixels (using info from header params)
	uint_fast32_t dataFieldBytes = width * height * (imagePixelSize / 8);
	TGAImg* img = calloc(HEADER_BYTES + dataFieldBytes, 1 );
	if (!img){
		printf("ERROR: calloc fail for img @ makeImage");
		exit(EXIT_FAILURE);
	}
	// Set header values
	img->idLength = idLength;
	img->colorMapType = colorMapType;
	img->imageType = imageType;
	img->colorMapOrigin = colorMapOrigin;
	img->colorMapLength = colorMapLength;
	img->colorMapEntrySize = colorMapEntrySize;
	img->xOrigin = xOrigin;
	img->yOrigin = yOrigin;
	img->width = width;
	img->height = height;
	img->imagePixelSize = imagePixelSize;
	img->imageDescriptorByte = imageDescriptorByte;
	return img;
}

// Writes contents of a TGAImg struct to a image of name imageName
void saveImage(char imageName[], TGAImg* img){
	FILE* imageFile = fopen(imageName, "wb");

	uint32_t imgSize = HEADER_BYTES + (img->width * img->height * (img->imagePixelSize / 8));
	fwrite(img, imgSize, 1, imageFile);

	fclose(imageFile);
}

void setPixel(TGAImg* img, RGB color, uint_fast32_t x, uint_fast32_t y){
	uint_fast32_t index = ((y * img->width) + x) * 3; // Convert x and y to index for array
	// Apply pixel change to all colors
	memcpy(&img->imageDataField[index], &color, 3);
}
