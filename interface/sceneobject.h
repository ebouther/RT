#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "editobject.h"
#include "ui_editobject.h"

class SceneObject
{
public:
    SceneObject(Ui::EditObject *ui);

    QString object_name;

    double pos_x;
    double pos_y;
    double pos_z;

    double rot_x;
    double rot_y;
    double rot_z;

    double col_r;
    double col_g;
    double col_b;

    double refl;
    double refr;

    double angle;
    double radius;
    double radius_2;

    double brim;
    double brip;
};

#endif // SCENEOBJECT_H
