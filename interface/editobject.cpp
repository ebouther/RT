#include "editobject.h"
#include "ui_editobject.h"
#include "editscene.h"

#include <QDir>
#include <QFileDialog>

EditObject::EditObject(QWidget *parent, QString object_name) :
    QDialog(parent),
    ui(new Ui::EditObject)
{
    ui->setupUi(this);
    this->parent = parent;
    ui->object_name->setText(object_name);
    col = new QColorDialog();
    col->show();
    QObject::connect(ui->import_tex, SIGNAL(clicked()), this, SLOT(import_tex()));
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

void  EditObject::import_tex()
{
    QString tex_file = QFileDialog::getOpenFileName(this,
        tr("Select an image file"), QDir::homePath(), tr("Image file(*.xpm)"));
    QFileInfo tex_path(tex_file);
    this->ui->tex_path->setText(tex_path.absoluteFilePath());
    if (this->ui->tex_path->text() == QDir::currentPath())
    this->ui->tex_path->setText("");
}
