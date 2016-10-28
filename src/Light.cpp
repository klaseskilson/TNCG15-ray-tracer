#include <Light.h>

Light::Light() {
//    Seen from below light:
//    a-----b           ^ z
//    | \   |           |
//    |   \ |           ----> x
//    c-----d
    dvec3 a(-1.0, 5.0, 8.0);
    dvec3 b(1.0, 5.0, 8.0);
    dvec3 c(-1.0, 5.0, 6.0);
    dvec3 d(1.0, 5.0, 6.0);

    const Surface White(ColorDouble(1.0f), LIGHTSOURCE);
    triangles.push_back(Triangle(a, d, b, White));
    triangles.push_back(Triangle(a, c, d, White));
}


const std::vector<Triangle> &Light::getTriangles() const {
    return triangles;
}

double Light::getLightIntensity() const {
    return lightIntensity;
}
