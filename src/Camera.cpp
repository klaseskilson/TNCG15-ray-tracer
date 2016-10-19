#include <iomanip>
#include <Camera.h>

Camera::Camera(bool cameraPosition) {
    eyeBeingUsed = cameraPosition;
    createPixels();
}

void Camera::createPixels() {
    for (int h = 0; h < HEIGHT; ++h) {
        for (int w = 0; w < WIDTH; ++w) {
            Pixel p(ColorDouble(0.0f));
            Ray r = getRayFromPixelCoords(w, h);
            p.setRay(r);
            pixels[h][w] = p;
        }
    }
}

/**
 * How to write to a PPM-image from:
 * https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
 *
 * @param scene the scene to take the image of
 * @param filename the name of the file to write to
 */
void Camera::createImage(Scene &scene, std::string filename) {
    std::cout << "Creating image..." << std::endl;
    FILE *fp = fopen(filename.c_str(), "wb"); /* b - binary mode */

    int count = 0, total = WIDTH * HEIGHT;
    (void) fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (auto row : pixels) {
        for (Pixel pixel : row) {
            // print progress
//            float progress = 100.0f * (float)count / total;
//            std::cout << "\r" << std::setw(7) << std::setprecision(5) << progress << "%";
//            std::cout << std::setprecision(5) << progress << "%" << std::endl;

            // get color
            ColorDouble clr = glm::normalize(pixel.getColorDouble(scene));
            int color[3] = {(int)(256 * clr.r), (int)(256 * clr.g), (int)(256 * clr.b)};
            (void) fwrite(color, 1, 3, fp);

            count += 1;
        }
    }
    (void) fclose(fp);

    std::cout << std::endl << "Wrote image to `" + filename + "`." << std::endl;
}

Ray Camera::getRayFromPixelCoords(const int w, const int h) {
    CameraPos c = getCamera();
    double pw = (double)w / WIDTH, ph = (double)h / HEIGHT;
    double radW = pw * fov - fov / 2, radH = ph * fov - fov / 2;
    double diffW = sin(radW), diffH = sin(radH);
    glm::vec3 diff(diffW, diffH, 0.0f);
    glm::vec3 lookAt = c.second + diff;
    Ray ray(c.first, lookAt);
    return ray;
};

CameraPos Camera::getCamera() {
    return eyeBeingUsed ? CAMERA_POS_1 : CAMERA_POS_2;
}

void Camera::setFov(float f) {
    fov = f;
}
