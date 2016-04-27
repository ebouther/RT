#include "editobject.h"
#include "ui_editobject.h"
#include <QColorDialog>

EditObject::EditObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditObject)
{
    ui->setupUi(this);
    QColorDialog col;
    col.show();
}

EditObject::~EditObject()
{
    delete ui;
}
