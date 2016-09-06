#ifndef TNCG15_COLORDOUBLE_H
#define TNCG15_COLORDOUBLE_H


class ColorDouble {
    ColorDouble() {
        return ColorDouble(glm::vec4(0.0));
    };
    ColorDouble(glm::vec4 color) {
        this.color = color;
    };
    ColorDouble(ColorDouble colorDouble) {
        return ColorDouble(colorDouble.getColor());
    };
    glm::vec4 getColor() {
        return this.color;
    };
private:
    glm::vec4 color;
};


#endif //TNCG15_COLORDOUBLE_H
