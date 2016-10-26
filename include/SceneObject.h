#ifndef TNCG15_SCENEOBJECT_H
#define TNCG15_SCENEOBJECT_H

#include "Surface.h"

class SceneObject {
public:
    virtual const glm::vec3 &getNormal(const vec3 &point = vec3(0.0)) const {
        return vec3(0.0);
    }

    const Surface &getSurface() const {
        return surface;
    }

protected:
    Surface surface;
};

#endif //TNCG15_SCENEOBJECT_H
