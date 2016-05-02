#include "editobject.h"
#include "ui_editobject.h"
#include "editscene.h"

EditObject::EditObject(QWidget *parent, QString object_name) :
    QDialog(parent),
    ui(new Ui::EditObject)
{
    ui->setupUi(this);
    this->parent = parent;
    ui->object_name->setText(object_name);
    col = new QColorDialog();
    col->show();
    QObject::connect(ui->add_object, SIGNAL(clicked()), this, SLOT(add_object()));
}

EditObject::~EditObject()
{
    delete ui;
}

void EditObject::add_object()
{
    ((EditScene *)parent)->add_object(this->ui);
    col->close();
    this->close();
}
