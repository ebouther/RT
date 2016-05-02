#include "sceneobject.h"

SceneObject::SceneObject(Ui::EditObject *ui)
{
    this->object_name = ui->object_name->text();

    this->pos_x = ui->pos_x->value();
    this->pos_x = ui->pos_x->value();
    this->pos_x = ui->pos_x->value();

    this->rot_x = ui->rot_x->value();
    this->rot_y = ui->rot_y->value();
    this->rot_z = ui->rot_z->value();

    this->dir_x = ui->dir_x->value();
    this->dir_y = ui->dir_y->value();
    this->dir_z = ui->dir_z->value();

    this->norm_x = ui->norm_x->value();
    this->norm_y = ui->norm_y->value();
    this->norm_z = ui->norm_z->value();

    this->col_r = ui->col_r->value() / 255;
    this->col_g = ui->col_g->value() / 255;
    this->col_b = ui->col_b->value() / 255;

    this->refl = ui->reflection->value();
    this->refr = ui->refraction->value();

    this->angle = ui->angle->value();

    this->radius = ui->radius->value();
    this->radius_2 = ui->radius_2->value();

    this->brim = ui->brim->value();
    this->brip = ui->brip->value();
}
