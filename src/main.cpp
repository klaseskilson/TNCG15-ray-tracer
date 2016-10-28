#include <Light.h>
#include "Box.h"
#include "Camera.h"
#include "Scene.h"

int main() {
    Scene scene;

    Box box(glm::vec3(0.0f, -2.0f, 5.0f), 2);
    Light areaLight;
//    scene.importTriangles(box.getTriangles());
    scene.importTriangles(areaLight.getTriangles());
    scene.addLight(areaLight);

    Camera cam(true);
    cam.setFov(M_PI / 1.5);

    // limit rendering numbers for debugging, comment out for magic result
    cam.setSpp(10);
    cam.setSubPixels(2);

    cam.createImage(scene);
    return 0;
}