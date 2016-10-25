//
// Created by Carl Englund on 2016-10-19.
//


#include <Light.h>

Light::Light() {

    vec3 topLeft (-1.0f, 5.0f, 8.0f);
    vec3 topRight(1.0f, 5.0f, 8.0f);
    vec3 bottomRight (-1.0f, 5.0f, 6.0f);
    vec3 bottomLeft (1.0f, 5.0f, 6.0f);

    const Surface White(ColorDouble(1.0f), 2);
    triangles.push_back(Triangle(bottomRight, topRight, bottomLeft, White));
    triangles.push_back(Triangle(bottomRight, bottomLeft, topLeft, White));
}

const std::vector<Triangle> &Light::getTriangles() const {
    return triangles;
}
