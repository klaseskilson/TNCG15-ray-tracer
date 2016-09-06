//
// Created by Carl Englund on 06/09/16.
//
#include <stdlib.h>
#include <stdio.h>
#include <Camera.h>
#include <iostream>

void Camera::render() {

}

/* How to write to a PPM-image from:
 * https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
 * */
void Camera::createImage() {

    std::cout << "Creating image...";

    FILE *fp = fopen("rayTracedImage.ppm", "wb"); /* b - binary mode */

    (void) fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    for (int j = 0; j < HEIGHT; ++j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            static unsigned char color[3];
            color[0] = i % 256;  /* red */
            color[1] = j % 256;  /* green */
            color[2] = (i * j) % 256;  /* blue */
            (void) fwrite(color, 1, 3, fp);
        }
    }
    (void) fclose(fp);

}

