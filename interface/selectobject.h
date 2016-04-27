#ifndef SELECTOBJECT_H
#define SELECTOBJECT_H

#include <QDialog>

namespace Ui {
class SelectObject;
}

class SelectObject : public QDialog
{
    Q_OBJECT

public:
    explicit SelectObject(QWidget *parent = 0);
    ~SelectObject();

public slots:
    void open_object_window();
private:
    Ui::SelectObject *ui;
};

#endif
