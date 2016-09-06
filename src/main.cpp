#include <iostream>

#include "RayTracer.h"
#include "Camera.h"

int main() {
    std::cout << "Hello world" << std::endl;
    Camera *cam = new Camera();
    cam->createImage();
    delete cam;
    return 0;
}