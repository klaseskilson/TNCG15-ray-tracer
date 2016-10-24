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
    ColorDouble max = castRays(scene);
    writeToFile(filename, max);
    std::cout << "DONE!" << std::endl;
}

/**
 * send rays into scnee
 * @param scene the scene
 * @return the maximum intensity found
 */
ColorDouble Camera::castRays(Scene &scene) {
    ColorDouble max(0.0f);
    std::cout << "Casting rays..." << std::endl;
    int count = 0, total = WIDTH * HEIGHT;
    for (auto &row : pixels) {
        for (Pixel &pixel : row) {
            // calculate progress
            float progress = 100.0f * (float)count / total;
            // pring progress (use one of the two lines)
//            std::cout << "\r" << std::setw(7) << std::setprecision(5) << progress << "%";
//            std::cout << std::setprecision(5) << progress << "%" << std::endl;

            // cast ray for this pixel
            Ray r = pixel.getFirstRay();
            ColorDouble clr = castRay(scene, r, pixel.getColorDouble());
            pixel.setColorDouble(clr);
            max = glm::max(max, clr);
            count += 1;
        }
    }

    return max;
}

void Camera::writeToFile(const std::string filename, const ColorDouble &max) {
    std::cout << "Writing image..." << std::endl;
    FILE *fp = fopen(filename.c_str(), "wb"); /* b - binary mode */
    (void) fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for (auto &row : pixels) {
        for (Pixel &pixel : row) {
            ColorDouble clr = pixel.getColorDouble();
            (void) fprintf(fp, "%d %d %d ",
                           (int)(255 * (clr.r / max.r)),
                           (int)(255 * (clr.g / max.g)),
                           (int)(255 * (clr.b / max.b)));
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

// TODO: split this mess somehow
ColorDouble Camera::castRay(Scene &scene, Ray &ray, const ColorDouble &inc, int reflections) {
    // get intersecting triangles in scene
    std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
    std::list<Sphere> sphereIntersections = scene.detectSphereIntersections(ray);
    ColorDouble clr(inc);

    // use for-in loop to pluck first intersection, if it exists
    for (TriangleIntersection &intersection : intersections) {
        Triangle t = intersection.t;
        // outgoing ray
        Ray out = ray.bounce(intersection.point, t.getNormal());

        double angle = glm::angle(ray.getDirection(), t.getNormal());
        ColorDouble emittance = t.getSurface().reflect(out, ray) * cos(angle);
        ray.setColor(emittance);
        clr += t.getSurface().reflect(out, ray) * cos(angle);

        // decide if we should terminate or not!
        if (reflections > 0) {
//            addRay(out);
            clr += castRay(scene, out, clr, reflections - 1);
        }
        break;
    }

    if(sphereIntersections.size() > 0) {
        clr = sphereIntersections.front().getColor();
    }

    return clr;
}
