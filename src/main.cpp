#include <iostream>
#include <Triangle.h>
#include <Ray.h>
#include "Camera.h"

int main() {
    Scene scene;
    Camera cam(true);
    cam.setFov(M_PI / 1.5);
    cam.setSpp(5);
    cam.createImage(scene);
    return 0;
}