#include "editscene.h"
#include "editobject.h"
#include "ui_editobject.h"
#include <QColorDialog>

EditObject::EditObject(QWidget *parent, QString object_name) :
    QDialog(parent),
    ui(new Ui::EditObject)
{
    ui->setupUi(this);
    ui->object_name->setText(object_name);
    col = new QColorDialog();
    col->setAttribute(Qt::WA_DeleteOnClose);
    col->show();
    //QObject::connect(ui->add_object, SIGNAL(clicked()), parent, SLOT(get_new_object()));
}

EditObject::~EditObject()
{
    delete col;
    delete ui;
}
