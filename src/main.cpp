#include <iostream>
#include <Triangle.h>
#include <Ray.h>
#include "Camera.h"

int main() {
    Camera *cam = new Camera(true);
    cam->createImage();
    delete cam;
    return 0;
}