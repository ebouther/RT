#ifndef SCENELIGHT_H
#define SCENELIGHT_H

#include "editlight.h"

class SceneLight
{
public:
    SceneLight(Ui::EditLight *ui);

    double pos_x;
    double pos_y;
    double pos_z;

    double col_r;
    double col_g;
    double col_b;

    double intensity;
};

#endif // SCENELIGHT_H
