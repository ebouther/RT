#ifndef EDITOBJECT_H
#define EDITOBJECT_H

#include <QDialog>
#include <QColorDialog>
#include <QDebug>
namespace Ui {
class EditObject;
}

class EditObject : public QDialog
{
    Q_OBJECT

public:
    explicit EditObject(QWidget *parent = 0, QString object_name = NULL);
    ~EditObject();
    Ui::EditObject *ui;

public slots:
     void add_object();
     void import_tex();

private:
    QWidget *parent;
    QColorDialog  *col;
};

#endif
