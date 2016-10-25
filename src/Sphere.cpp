//
// Created by Carl Englund on 2016-10-20.
//
#include <Triangle.h>
#include "Sphere.h"
#define EPSILON 0.00000000000000001


Sphere::Sphere(glm::vec3 mPosition, float mRadius, Surface mSurface) {
    position = mPosition;
    radius = mRadius;
    surface = mSurface;
}

int Sphere::sphereIntersection(Ray& ray, glm::vec3 &intersection) {
    //Ray offset from sphere center
   glm::vec3 normalizedRayDirection = glm::normalize(ray.getDirection());
   glm::vec3 rayOrigin = ray.getStart();
   glm::vec3 sphereCenter = this->position;
   float sphereRadius = this->radius;

   float b = glm::dot((2.0f*normalizedRayDirection), (rayOrigin-sphereCenter));
   float ac = glm::dot(rayOrigin-sphereCenter, rayOrigin-sphereCenter)-glm::pow(sphereRadius, 2);
   float d1 = -b / 2.0f;
   float d2 = d1;
   float bsqrt = glm::pow(d1, 2) - ac;
   d1 += bsqrt;
   d2 -= bsqrt;
   if(bsqrt < EPSILON)
       return NOT_INTERSECTION;

    bsqrt = glm::sqrt(bsqrt);
   if(d1 <= 0 && d2 <= 0){
   }
   else if(d2 < d1) {
       intersection = rayOrigin + d2*normalizedRayDirection;
       return INTERSECTION;
   }
   else if(d1 < d2) {
       intersection = rayOrigin + d1*normalizedRayDirection;
       return INTERSECTION;
   }
   else {
       intersection = rayOrigin + d2*normalizedRayDirection;
       return INTERSECTION;
   }

   //This will never happen.
   return NOT_INTERSECTION;


}

const glm::vec3 &Sphere::getNormal(vec3 point) const {
    vec3 normal = glm::normalize(point - position);
    return normal;
};

const Surface &Sphere::getSurface() const {
    return surface;
}
