#include "Pixel.h"

Pixel::Pixel(ColorDouble colorDbl) {
    colorDouble = colorDbl;
}

ColorDouble Pixel::castRay(Scene &scene, const Ray &ray, int reflections) {
    // get intersecting triangles in scene
    std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
    std::list<Sphere> sphereIntersections = scene.detectSphereIntersections(ray);
    glm::vec3 rayStart = ray.getStart();

    // only use the closest ray
    intersections.sort([&rayStart](TriangleIntersection &a, TriangleIntersection &b) {
        return glm::length(glm::distance(a.point, rayStart)) < glm::length(glm::distance(b.point, rayStart));
    });

    // this is wrong, do not use every triangle that is hit!
    for (TriangleIntersection &intersection : intersections) {
        Triangle t = intersection.t;
        colorDouble += t.getColor();

        // bounce this array
        if (reflections > 0) {
            glm::vec3 newDirection = glm::reflect(ray.getDirection(), t.getNormal());
            Ray r(intersection.point, newDirection);
            addRay(r);
            castRay(scene, r, reflections - 1);
        }
        // TODO: remove this break, use proper way of collecting colors from collisions
        break;
    }

    if(sphereIntersections.size() > 0) {
        colorDouble = sphereIntersections.front().getColor();
    }


    return colorDouble;
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
