#include "scenelight.h"
#include "editlight.h"
#include "ui_editlight.h"

SceneLight::SceneLight(Ui::EditLight *ui)
{
    this->pos_x = ui->pos_x->value();
    this->pos_x = ui->pos_x->value();
    this->pos_x = ui->pos_x->value();

    this->col_r = ui->col_r->value() / 255;
    this->col_g = ui->col_g->value() / 255;
    this->col_b = ui->col_b->value() / 255;

    this->intensity = ui->intensity->value();
}
