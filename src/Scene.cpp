#include "Scene.h"

Scene::Scene() {
    createRoom();
}

void Scene::createRoom() {
// View from above:
// ^ = camera 1 and viewing direction (origo)
// v = camera 2 and viewing direction
//           a
//          / \   <-- front
// LEFT    b v c     RIGHT
//         |   |  <-- center
//         d ^ e
//          \ /   <-- back
//           f
//
//    ^ z
//    |
//    |----> x

    glm::vec3 aBottom(0.0f, -5.0f, 13.0f), aTop(0.0f, 5.0f, 13.0f);
    glm::vec3 bBottom(-6.0f, -5.0f, 10.0f), bTop(-6.0f, 5.0f, 10.0f);
    glm::vec3 cBottom(6.0f, -5.0f, 10.0f), cTop(6.0f, 5.0f, 10.0f);
    glm::vec3 dBottom(-6.0f, -5.0f, 0.0f), dTop(-6.0f, 5.0f, 0.0f);
    glm::vec3 eBottom(6.0f, -5.0f, 0.0f), eTop(6.0f, 5.0f, 0.0f);
    glm::vec3 fBottom(0.0f, -5.0f, -3.0f), fTop(0.0f, 5.0f, -3.0f);

    const Surface White(ColorDouble(1.0f));
    const Surface Grey(ColorDouble(0.5f));
    const Surface Red(ColorDouble(1.0f, 0.0f, 0.0f));
    const Surface Green(ColorDouble(0.0f, 1.0f, 0.0f));
    const Surface Blue(ColorDouble(0.0f, 0.0f, 1.0f));
    const Surface Yellow(ColorDouble(1.0f, 1.0f, 0.0f));
    const Surface Purple(ColorDouble(1.0f, 0.0f, 1.0f));
    const Surface Teal(ColorDouble(0.0f, 0.0f, 0.0f), SPECULAR);
    const Surface Mirror(ColorDouble(0.0f), SPECULAR);

    // Floor
    triangles.push_back(Triangle(bBottom, cBottom, aBottom, White));
    triangles.push_back(Triangle(bBottom, dBottom, cBottom, White));
    triangles.push_back(Triangle(dBottom, eBottom, cBottom, White));
    triangles.push_back(Triangle(dBottom, fBottom, eBottom, White));
    // Roof
    triangles.push_back(Triangle(bTop, aTop, cTop, White));
    triangles.push_back(Triangle(bTop, cTop, dTop, White));
    triangles.push_back(Triangle(dTop, cTop, eTop, White));
    triangles.push_back(Triangle(dTop, eTop, fTop, White));
    // Right side back
    triangles.push_back(Triangle(fBottom, fTop, eTop, Blue));
    triangles.push_back(Triangle(fBottom, eTop, eBottom, Blue));
    // Left side back
    triangles.push_back(Triangle(dBottom, dTop, fTop, Yellow));
    triangles.push_back(Triangle(dBottom, fTop, fBottom, Yellow));
    // Left side center
    triangles.push_back(Triangle(bBottom, bTop, dTop, Yellow));
    triangles.push_back(Triangle(bBottom, dTop, dBottom, Yellow));
    // Left side front
    triangles.push_back(Triangle(aBottom, aTop, bTop, Purple));
    triangles.push_back(Triangle(aBottom, bTop, bBottom, Purple));
    // Right side front
    triangles.push_back(Triangle(cBottom, cTop, aTop, Teal));
    triangles.push_back(Triangle(cBottom, aTop, aBottom, Teal));
    // Right side center
    triangles.push_back(Triangle(eBottom, eTop, cTop, Blue));
    triangles.push_back(Triangle(eBottom, cTop, cBottom, Blue));
}

void Scene::importTriangles(std::vector<Triangle> triangles) {
    for (Triangle &t : triangles) importTriangle(t);
}

void Scene::importTriangle(Triangle &t) {
    triangles.push_back(t);
}

/**
 * detect ray intersection
 * @param ray
 * @return list of TriangleIntersections, sorted by distance to ray start
 */
std::list<TriangleIntersection> Scene::detectIntersections(Ray ray) const {
    std::list<TriangleIntersection> intersections = {};
    for (Triangle triangle : triangles) {
        TriangleIntersection ti;
        glm::vec3 intersection;
        int result = triangle.intersection(ray, intersection);
        if (result == INTERSECTION) {
            // intersection found, add it to the list of intersections
            ti.triangle = triangle;
            ti.point = intersection + 0.0001f*-triangle.getNormal();
            intersections.push_back(ti);
        }
    }
    vec3 rayStart = ray.getStart();
    intersections.sort([&rayStart](const auto &a, const auto &b) {
        return glm::length(a.point - rayStart) < glm::length(b.point - rayStart);
    });
    return intersections;
};

std::list<SphereIntersection> Scene::detectSphereIntersections(Ray ray) const {
    std::list<SphereIntersection> intersectingSpheres = {};
    for(Sphere s : spheres) {
        glm::vec3 intersection;
        SphereIntersection si;
        int result = s.sphereIntersection(ray, intersection);
        if(result == INTERSECTION) {
            si.sphere = s;
            si.point = intersection + 0.0001f*s.getNormal(intersection);
            intersectingSpheres.push_back(si);
        }
    }
    return intersectingSpheres;
};

ColorDouble Scene::getLightContribution(const vec3 &point, const vec3 &normal) const {
    ColorDouble clr(0.0);
    int lightCount = 0;
    double lightArea = 0.0;
    for (Light light : lights) {
        for (Triangle lightTriangle : light.getTriangles()) {
            lightArea += lightTriangle.area();
            for (int i = 0; i < SHADOW_RAY_COUNT; ++i) {

                ++lightCount;
                // create shadowrays point -> light
                vec3 lightPoint = lightTriangle.getRandomPoint();
                Ray rayTowardsLight(point, glm::normalize(lightPoint - point));

                // visibility check
                std::list<SphereIntersection> sphereIntersections = detectSphereIntersections(rayTowardsLight);
                std::list<TriangleIntersection> triangleIntersections = detectIntersections(rayTowardsLight);
                TriangleIntersection intersection = triangleIntersections.front();
                double lightDistance = glm::distance(point, lightPoint);

                if (sphereIntersections.size() > 0 || glm::distance(point, intersection.point) < lightDistance) {
                    // not visible!
                    continue;
                }

                // calc geometric term
                double alpha = glm::dot(-normal, rayTowardsLight.getDirection());
                double beta = glm::clamp((double) glm::dot(lightTriangle.getNormal(), -rayTowardsLight.getDirection()), 0.0, 1.0);

                double geometric = alpha * beta / pow(lightDistance, 2.0);
                Surface lightSurface = lightTriangle.getSurface();
                clr += lightSurface.getColor() * lightSurface.getEmission() * geometric;
            }
        }
    }




    return clr * lightArea / (double)lightCount;
}
