#include <Camera.h>

Camera::Camera(bool cameraPosition) {
    eyeBeingUsed = cameraPosition;
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
    double max = castRays(scene);
    writeToFile(filename, max);
    std::cout << "DONE!" << std::endl;
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
 * send rays into scnee
 * @param scene the scene
 * @return the maximum intensity found
 */
double Camera::castRays(Scene &scene) {
    double maximum = 0.0;
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
                    clr += castRay(scene, r);
                }
            }
            clr /= (double) (spp * subPixels * subPixels);
            pixel.setColorDouble(clr);
            maximum = glm::max(maximum, glm::max(clr.r, glm::max(clr.g, clr.b)));
            count += 1;
        }
    }
    return maximum;
}

void Camera::writeToFile(const std::string filename, const double &max) {
    std::cout << std::endl << std::endl << "Writing image... (Max: " << max << ")" << std::endl;
    FILE *fp = fopen(filename.c_str(), "wb"); /* b - binary mode */
    (void) fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for (auto &row : pixels) {
        for (Pixel &pixel : row) {
            ColorDouble clr = pixel.getColorDouble();
            (void) fprintf(fp, "%d %d %d ",
                           (int)(255 * (clr.r / max)),
                           (int)(255 * (clr.g / max)),
                           (int)(255 * (clr.b / max)));
        }
    }
    (void) fclose(fp);
    std::cout << std::endl << "Wrote image to `" + filename + "`." << std::endl;
}

Ray Camera::getRayFromPixelCoords(const double w, const double h) {
    CameraPos c = getCamera();
    double aspectRatio = (double)HEIGHT / (double)WIDTH;
    double pw = w / WIDTH, ph = h / HEIGHT;
    double fovH = fov * aspectRatio;
    double radW = pw * fov - fov / 2, radH = ph * fovH - fovH / 2;
    double diffW = -sin(radW), diffH = -sin(radH);
    glm::vec3 diff(diffW, diffH, 0.0f);
    glm::vec3 lookAt = glm::normalize(c.second + diff);
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
ColorDouble Camera::castRay(Scene &scene, Ray &ray, int depth) {
    // get intersecting triangles in scene
    std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
    std::list<SphereIntersection> sphereIntersections = scene.detectSphereIntersections(ray);
    ColorDouble clr(0.0);
    float distanceToSphere = INFINITY;
    float distanceToTriangle = INFINITY;

    if (sphereIntersections.size()) {
        distanceToSphere = glm::distance(sphereIntersections.front().point, ray.getStart());
    }
    if(intersections.size() > 0) {
        distanceToTriangle = glm::distance(intersections.front().point, ray.getStart());
    }

    if(!sphereIntersections.size() && !intersections.size()) {
        std::cout << "Poop" << std::endl;
    }

    if(distanceToTriangle < distanceToSphere) {
        for (TriangleIntersection &intersection : intersections) {
            Triangle t = intersection.triangle;
            Surface surface = t.getSurface();
            //Area light test.
            if(surface.hasReflectionModel(LIGHTSOURCE))  {
                clr = surface.getColor();// * surface.getEmission();
                break;
            }
            vec3 normal = t.getNormal();
            Ray out = surface.bounceRay(ray, intersection.point, normal);
            double angle = glm::angle(out.getDirection(), normal);
            ColorDouble emittance = surface.reflect(ray, out, normal) * cos(angle);
            const ColorDouble &lightContribution = scene.getLightContribution(intersection.point, normal);
            clr += emittance;
            clr *= lightContribution;

            // decide if we should terminate or not!
            double rrTop = glm::max(glm::max(emittance.r, emittance.g), emittance.b);
            if (depth < MAX_DEPTH || uniformRand() < rrTop) {
                int nextDepth = surface.hasReflectionModel(SPECULAR) ? depth : depth + 1;
                clr += castRay(scene, out, nextDepth) * surface.getReflectionCoefficient();
            }
            break;
        }
    } else {
        for(SphereIntersection &sphereIntersection : sphereIntersections) {
            Sphere s = sphereIntersection.sphere;
            Surface surface = s.getSurface();

            const vec3 &normal = s.getNormal(sphereIntersection.point);
            Ray out = surface.bounceRay(ray, sphereIntersection.point, normal);
            double angle = glm::angle(out.getDirection(), normal);

            ColorDouble emittance = surface.reflect(out, ray, normal) * cos(angle);
            ColorDouble lightContribution = scene.getLightContribution(sphereIntersection.point, normal);
            clr += emittance;
            clr *= lightContribution;

            // decide if we should terminate or not!
            double rrTop = glm::max(glm::max(emittance.r, emittance.g), emittance.b);
            if (depth < MAX_DEPTH || uniformRand() < rrTop) {
                int nextDepth = surface.hasReflectionModel(SPECULAR) ? depth : depth + 1;
                clr += castRay(scene, out, nextDepth) * surface.getReflectionCoefficient();
            }
            break;
        }
    }


    return clr;
}

void Camera::setSpp(int spp) {
    Camera::spp = spp;
}

void Camera::setSubPixels(int subPixels) {
    Camera::subPixels = subPixels;
}
