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
            p.addRay(r);
            pixels[h][w] = p;
        }
    }
}

/**
 * Write PPM image
 *
 * @param scene the scene to take the image of
 * @param filename the name of the file to write to
 */
void Camera::createImage(Scene &scene, std::string filename) {
    std::cout << "Creating image..." << std::endl;
    double max = castRays(scene);
    writeToFile(filename, max);
    std::cout << "DONE!" << std::endl;
}

double Camera::castRays(Scene &scene) {
    std::cout << "Casting rays..." << std::endl;
    int count = 0, total = WIDTH * HEIGHT;
    for (auto &row : pixels) {
        for (Pixel &pixel : row) {
            // print progress
            float progress = 100.0f * (float)count / total;
//            std::cout << "\r" << std::setw(7) << std::setprecision(5) << progress << "%";
            std::cout << std::setprecision(5) << progress << "%" << std::endl;

            // cast ray for this pixel
            pixel.castRay(scene);
            count += 1;
        }
    }

    return 0.0;
}

void Camera::writeToFile(const std::string filename, const double &max) {
    std::cout << "Writing image..." << std::endl;
    FILE *fp = fopen(filename.c_str(), "wb"); /* b - binary mode */
    (void) fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for (auto &row : pixels) {
        for (Pixel &pixel : row) {
            ColorDouble clr = pixel.getColorDouble();
            (void) fprintf(fp, "%d %d %d ",
                           (int)(255 * clr.r),
                           (int)(255 * clr.g),
                           (int)(255 * clr.b));
        }
    }
    (void) fclose(fp);
    std::cout << std::endl << "Wrote image to `" + filename + "`." << std::endl;
}

Ray Camera::getRayFromPixelCoords(const int w, const int h) {
    CameraPos c = getCamera();
    double pw = (double)w / WIDTH, ph = (double)h / HEIGHT;
    double radW = pw * fov - fov / 2, radH = ph * fov - fov / 2;
    double diffW = -sin(radW), diffH = -sin(radH);
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
