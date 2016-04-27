#ifndef EDITOBJECT_H
#define EDITOBJECT_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class EditObject;
}

class EditObject : public QDialog
{
    Q_OBJECT

public:
    explicit EditObject(QWidget *parent = 0);
    ~EditObject();

private:
    Ui::EditObject *ui;
};

#endif
