/* Aidan Trent
 * An implementation of 24 bit TARGA image (create, manipulate pixels, and export)
 * Put together with a elementary understanding of C
 * Made with info from https://www.gamers.org/dEngine/quake3/TGA.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEADER_BYTES 18 // Ammount of bytes header should take up

struct TGAImg{
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
};

struct Color{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct TGAImg* makeImg(uint8_t idLength, uint8_t colorMapType,
						uint8_t imageType, uint16_t colorMapOrigin,
						uint16_t colorMapLength, uint8_t colorMapEntrySize,
						uint16_t xOrigin, uint16_t yOrigin,
						uint16_t width, uint16_t height,
						uint8_t imagePixelSize, uint8_t imageDescriptorByte){
	// Allocate memory for header + image pixels (using info from header params) + 32 bit int w/ ammount of bytes in datafield
	uint32_t dataFieldBytes = width * height * (imagePixelSize / 8);
	struct TGAImg* img = calloc(HEADER_BYTES + dataFieldBytes + sizeof(uint32_t), 1 );
	if (!img){
		printf("ERROR: malloc fail for img @ makeImg");
		exit(EXIT_FAILURE);
	}
	// SET HEADER VALUES
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
void saveImage(char imageName[], struct TGAImg* img){
	FILE* imageFile = fopen(imageName, "wb");
	// WRITE HEADER
	fwrite(&img->idLength, sizeof(img->idLength), 1, imageFile);
	fwrite(&img->colorMapType, sizeof(img->colorMapType), 1, imageFile);
	fwrite(&img->imageType, sizeof(img->imageType), 1, imageFile);
	fwrite(&img->colorMapOrigin, sizeof(img->colorMapOrigin), 1, imageFile);
	fwrite(&img->colorMapLength, sizeof(img->colorMapLength), 1, imageFile);
	fwrite(&img->colorMapEntrySize, sizeof(img->colorMapEntrySize), 1, imageFile);
	fwrite(&img->xOrigin, sizeof(img->xOrigin), 1, imageFile);
	fwrite(&img->yOrigin, sizeof(img->yOrigin), 1, imageFile);
	fwrite(&img->width, sizeof(img->width), 1, imageFile);
	fwrite(&img->height, sizeof(img->height), 1, imageFile);
	fwrite(&img->imagePixelSize, sizeof(img->imagePixelSize), 1, imageFile);
	fwrite(&img->imageDescriptorByte, sizeof(img->imageDescriptorByte), 1, imageFile);
	fwrite(&img->imageDataField, img->width * img->height * (img->imagePixelSize / 8), 1, imageFile);
}

void setPixel(struct TGAImg* img, struct Color color, int x, int y){
	uint32_t index = ((y * img->width) + x) * 3; // Convert x and y to index for array

	// Apply pixel change to all colors
	img->imageDataField[index] = color.blue;
	img->imageDataField[index+1] = color.green;
	img->imageDataField[index+2] = color.red;
}
