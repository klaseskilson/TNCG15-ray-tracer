#include <iostream>
#include <Triangle.h>
#include <Ray.h>
#include "Camera.h"

int main() {
    Camera *cam = new Camera(true);
    Scene s;
    cam->createImage(s);
    return 0;
}