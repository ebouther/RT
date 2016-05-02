#include "editlight.h"
#include "ui_editlight.h"
#include "editscene.h"

#include <QObject>

EditLight::EditLight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLight)
{
    ui->setupUi(this);
    this->parent = parent;
    QObject::connect(ui->add_light, SIGNAL(clicked()), this, SLOT(add_light()));
}

EditLight::~EditLight()
{
    delete ui;
}

void EditLight::add_light()
{
    ((EditScene *)parent)->add_light(this->ui);
    this->close();
}
