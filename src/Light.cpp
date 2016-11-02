#include <Light.h>

Light::Light() {
//    Seen from below light:
//    a-----b           ^ z
//    | \   |           |
//    |   \ |           ----> x
//    c-----d
    dvec3 a(-1.0, 4.99, 8.0);
    dvec3 b(1.0, 4.99, 8.0);
    dvec3 c(-1.0, 4.99, 6.0);
    dvec3 d(1.0, 4.99, 6.0);

    const Surface white(ColorDouble(1.0f), LIGHTSOURCE);
    triangles.push_back(Triangle(a, d, b, white));
    triangles.push_back(Triangle(a, c, d, white));
}


const std::vector<Triangle> &Light::getTriangles() const {
    return triangles;
}
