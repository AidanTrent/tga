/* Aidan Trent
 * Creates an example tga image
 * Put together with a elementary understanding of C
 */
#include "tga.h"
#include <stdio.h>

#define UNCOMP_RGB 2 // Uncompressed RGB image type
#define IMG_PIXEL_SIZE 24 // 24 bits for RGB. 32 bits for alpha (not implemented)

int main(void){
	int width = 500;
	int height = 500;

	struct TGAImg* image = makeImg(0, 0, UNCOMP_RGB, 0, 0, 0, 0, 0, width, height, IMG_PIXEL_SIZE, 0);
	struct Color color = {0,0,0};

	float redIntermediate = 0;
	float blueIntermediate = 0;
	float widthInc = (255. / width);
	float heightInc = (255. / height);

	for (int y = 0; y < height; y++){
		redIntermediate += heightInc;
		color.blue = redIntermediate;
		blueIntermediate = 0;
		for (int x = 0; x < width; x++){
			blueIntermediate += widthInc;
			color.red = blueIntermediate;
			setPixel(image, color, x, y);
		}
	}

	saveImage("testImage.tga", image);
}
