//
// Created by Carl Englund on 2016-10-20.
//
#include "Sphere.h"
#define EPSILON 0.00000000000000001


Sphere::Sphere(glm::vec3 mPosition, float mRadius, ColorDouble mColor) {
    position = mPosition;
    radius = mRadius;
    color = mColor;
}

int Sphere::sphereIntersection(Ray& ray, glm::vec3 &intersection) {
    //Ray offset from sphere center
    glm::vec3 oc = position - ray.getStart();
    float b = glm::dot(ray.getDirection()*2.0f, oc);
    float d1 = -b/2.0f;
    float d2 = d1;
    float delta = std::pow(d1, 2) - (glm::dot(oc, oc) - std::pow(radius, 2));

    if(delta < -EPSILON) {
        return false;
    }
    else if( delta > -EPSILON && delta < EPSILON) {
        intersection = ray.getStart()+d1*ray.getDirection();
        return true;
    }

    float dSqrt = std::sqrt(delta);

    d1 -= dSqrt;
    d2 += dSqrt;

    if(d1 > EPSILON) {
        intersection = ray.getStart()+d1*ray.getDirection();
        return true;
    }
    else if(d2 > EPSILON) {
        intersection = ray.getStart()+d2*ray.getDirection();
        return true;
    }

    return false;
}

const ColorDouble &Sphere::getColor() const {
    return color;
}
