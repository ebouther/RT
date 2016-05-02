#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "editobject.h"
#include "ui_editobject.h"
#include "selectobject.h"
#include "sceneobject.h"

#include <QDialog>
#include <QList>

namespace Ui {
class EditScene;
}

class EditScene : public QDialog
{
    Q_OBJECT

public:
    explicit EditScene(QWidget *parent = 0);
    ~EditScene();
    void add_object(Ui::EditObject *obj);
    static QList<SceneObject*> objs;

public slots:
    void open_object_window();

private:
    Ui::EditScene *ui;
    void fill_obj_list();
};

#endif
