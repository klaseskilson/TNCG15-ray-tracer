#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

// TODO: move this mess somehow
ColorDouble Pixel::castRay(Scene &scene, const Ray &ray, const ColorDouble &inc, int reflections) {
    // get intersecting triangles in scene
    std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
    std::list<Sphere> sphereIntersections = scene.detectSphereIntersections(ray);
    glm::vec3 rayStart = ray.getStart();

    ColorDouble clr(inc);

    // use for-in loop to pluck first intersection, if it exists
    for (TriangleIntersection &intersection : intersections) {
        Triangle t = intersection.t;

        // dE = cos(theta) L dw
        // dL =
        // fr = dL(w0)/dE(wi)
        //
        // diffuse:
        // L = fr * pi

        // the rendering equation
        double angle = glm::angle(ray.getDirection(), t.getNormal());
        // might be the radiosity
        clr += t.getColor() * dvec3(cos(angle));

        // bounce this array, recursive call
        if (reflections > 0) {
            Ray r = ray.bounce(intersection.point, t.getNormal());
            addRay(r);
            clr += castRay(scene, r, clr, reflections - 1);
        }
        break;
    }

    if(sphereIntersections.size() > 0) {
        clr = sphereIntersections.front().getColor();
    }

    return clr;
}

const ColorDouble &Pixel::getColorDouble() const {
    return colorDouble;
}

void Pixel::addRay(Ray &r) {
    rayList.push_back(r);
}

Ray Pixel::getFirstRay() {
    return rayList[0];
}

void Pixel::setColorDouble(const ColorDouble &colorDouble) {
    Pixel::colorDouble = colorDouble;
}
