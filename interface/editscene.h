#ifndef EDITSCENE_H
#define EDITSCENE_H

#include <QDialog>

namespace Ui {
class EditScene;
}

class EditScene : public QDialog
{
    Q_OBJECT

public:
    explicit EditScene(QWidget *parent = 0);
    ~EditScene();
    static void add_object();

public slots:
    void open_object_window();

private:
    Ui::EditScene *ui;
    void fill_obj_list();
};

#endif
