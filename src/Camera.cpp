#include <Camera.h>

void Camera::render() {

}

/* How to write to a PPM-image from:
 * https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
 * */
void Camera::createImage(std::string filename) {

    std::cout << "Creating image...";

    FILE *fp = fopen(filename.c_str(), "wb"); /* b - binary mode */

    (void) fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (auto row : pixels) {
        for (Pixel pixel : row) {
            ColorDouble clr = pixel.getColorDouble();
            int color[3] = {(int)(256 * clr.r), (int)(256 * clr.g), (int)(256 * clr.b)};
            (void) fwrite(color, 1, 3, fp);
        }
    }
    (void) fclose(fp);

    std::cout << " wrote image to `" + filename + "`.";
}

