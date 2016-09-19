#include <iostream>
#include <Triangle.h>
#include <Ray.h>
#include "RayTracer.h"
#include "Camera.h"

int main() {
    Camera *cam = new Camera();
    cam->createImage();
    delete cam;
    return 0;
}