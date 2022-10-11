/* Aidan Trent
 * Creates an example tga image
 * Put together with a elementary understanding of C
 */
#include "tga.h"
#include <stdio.h>

#define UNCOMP_RGB 2 // Uncompressed RGB image type
#define IMG_PIXEL_SIZE 24 // 24 bits for RGB. 32 bits for RGB+alpha (not implemented)

int main(void){
	int width = 30;
	int height = 30;

	TGAHeader header = {0, 0, UNCOMP_RGB, 0, 0, 0, 0, 0, width, height, IMG_PIXEL_SIZE, 0};
	TGAImg* image = makeImage(&header);
	RGB color = {0,0,0};

	float blueIntermediate = 0;
	float redIntermediate = 0;
	float widthInc = (255. / width);
	float heightInc = (255. / height);

	for (int y = 0; y < height; y++){
		blueIntermediate += heightInc;
		color.blue = blueIntermediate;
		redIntermediate = 0;
		for (int x = 0; x < width; x++){
			redIntermediate += widthInc;
			color.red = redIntermediate;
			setPixel(image, color, x, y);
		}
	}

	saveImage("testImage.tga", image);
	TGAImg* image2 = loadImage("testImage.tga");
	if (image2 != NULL){
		saveImage("testImage2.tga", image2);
	}
}
