#include <iostream>

#include "RayTracer.h"
#include "Camera.h"

int main() {
    Camera *cam = new Camera();
    cam->createImage();
    delete cam;
    return 0;
}