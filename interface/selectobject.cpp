#include "selectobject.h"
#include "ui_selectobject.h"
#include "editobject.h"


SelectObject::SelectObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectObject)
{
    ui->setupUi(this);
    this->parent = parent;
    QObject::connect(ui->b_select, SIGNAL(clicked()), this, SLOT(open_object_window()));
}

SelectObject::~SelectObject()
{
    delete ui;
}

void SelectObject::open_object_window()
{
    QList<QListWidgetItem *> objects = ui->object_list->selectedItems();
    if (objects.count() != 0)
    {
        //objects->front();
        EditObject *obj = new EditObject(this->parentWidget(), objects.first()->text());
        this->close();
        obj->show();
    }
}
