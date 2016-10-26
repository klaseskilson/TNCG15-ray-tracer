#include <Camera.h>

Camera::Camera(bool cameraPosition) {
    eyeBeingUsed = cameraPosition;
}

void Camera::createPixels() {
    for (int h = 0; h < HEIGHT; ++h) {
        for (int w = 0; w < WIDTH; ++w) {
            Pixel p(ColorDouble(0.0f));

            float diff = 1.0f / subPixels;
            for (int subX = 0; subX < subPixels; ++subX) {
                for (int subY = 0; subY < subPixels; ++subY) {
                    double x = randMinMax(w + subX * diff, w + (subX + 1) * diff);
                    double y = randMinMax(h + subY * diff, h + (subY + 1) * diff);
                    Ray r = getRayFromPixelCoords(x, y);
                    p.addRay(r);
                }
            }

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
    std::cout << "Creating " << WIDTH << "x" << HEIGHT << " image..." << std::endl;
    std::cout << "SPP: " << spp
              << ". Subpixels: " << subPixels
              << ". Camera: " << glm::to_string(getCamera().first) << "." << std::endl;
    createPixels();
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
            std::cout << "\r" << progress << "%";
//            std::cout << std::setprecision(5) << progress << "%" << std::endl;

            // cast ray for this pixel
            ColorDouble clr(0.0);
            std::vector<Ray> rays = pixel.getRayList();
            for (Ray r : rays) {
                for (int i = 0; i < spp; ++i) {
                    clr += castRay(scene, r, pixel.getColorDouble());
                }
            }
            clr /= (double) (spp * subPixels * subPixels);
            pixel.setColorDouble(clr);
            max = glm::max(max, clr);
            count += 1;
        }
    }

    return max;
}

void Camera::writeToFile(const std::string filename, const ColorDouble &max) {
    std::cout << std::endl << std::endl << "Writing image..." << std::endl;
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
    double aspectRatio = (double)HEIGHT / (double)WIDTH;
    double pw = (double)w / WIDTH, ph = (double)h / HEIGHT;
    double fovH = fov * aspectRatio;
    double radW = pw * fov - fov / 2, radH = ph * fovH - fovH / 2;
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
ColorDouble Camera::castRay(Scene &scene, Ray &ray, const ColorDouble &inc, int depth) {
    // get intersecting triangles in scene
    std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
    std::list<SphereIntersection> sphereIntersections = scene.detectSphereIntersections(ray);
    ColorDouble clr(inc);
    float dTs;
    float dTt;

    if(sphereIntersections.size() > 0 && intersections.size() > 0) {
        dTs = glm::length(sphereIntersections.front().point - ray.getStart());
        dTt = glm::length(intersections.front().point - ray.getStart());
    }
    if(!sphereIntersections.size() || (sphereIntersections.size() && intersections.size() && dTs > dTt)) {
        for (TriangleIntersection &intersection : intersections) {
            Triangle t = intersection.triangle;
            Surface s = t.getSurface();

            //Area light test.
            if(s.hasReflectionModel(LIGHTSOURCE))  {
                clr = s.getColor();
                break;
            }

            Ray out = s.bounceRay(ray, intersection.point, t.getNormal());
            double angle = glm::angle(ray.getDirection(), t.getNormal());

            ColorDouble emittance = s.reflect(ray, out, t.getNormal()) * cos(angle) * pow(s.getReflectionCoefficient(), (double)depth);
            ray.setColor(emittance);
            clr += emittance;
            clr *= scene.getLightEffects(intersection.point, t.getNormal());

            // decide if we should terminate or not!
            double rrTop = glm::max(glm::max(emittance.r, emittance.g), emittance.b);
            if (depth < MAX_DEPTH || uniformRand() < rrTop) {
    //            addRay(out);
                int nextDepth = s.hasReflectionModel(SPECULAR) ? depth : depth + 1;
                clr += castRay(scene, out, clr, nextDepth);
            }
            break;
        }
    }
    for(SphereIntersection &sphereIntersection : sphereIntersections) {
        Sphere s = sphereIntersection.sphere;
        Surface sphereSurface = s.getSurface();

        Ray out = sphereSurface.bounceRay(ray, sphereIntersection.point, s.getNormal(sphereIntersection.point));
        double angle = glm::angle(ray.getDirection(), s.getNormal(sphereIntersection.point));

        ColorDouble emittance = sphereSurface.reflect(out, ray, s.getNormal(sphereIntersection.point)) * cos(angle)
                                * pow(sphereSurface.getReflectionCoefficient(), (double)depth);
        ray.setColor(emittance);
        clr += emittance;
        clr *= scene.getLightEffects(sphereIntersection.point, s.getNormal(sphereIntersection.point));

        // decide if we should terminate or not!
        double rrTop = glm::max(glm::max(emittance.r, emittance.g), emittance.b);
        if (depth < 5 || uniformRand() < rrTop) {
///           addRay(out);
            clr += castRay(scene, out, clr, depth + 1);
        }
        break;
    }


    return clr;
}

void Camera::setSpp(int spp) {
    Camera::spp = spp;
}

void Camera::setSubPixels(int subPixels) {
    Camera::subPixels = subPixels;
}
