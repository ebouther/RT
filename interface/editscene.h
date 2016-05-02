#ifndef EDITSCENE_H
#define EDITSCENE_H

#include "editobject.h"
#include "ui_editobject.h"
#include "selectobject.h"
#include "sceneobject.h"
#include "scenelight.h"

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
    void add_light(Ui::EditLight *light);
    static QList<SceneObject*> objs;
    static QList<SceneLight*> lights;

public slots:
    void open_object_window();
    void open_light_window();
    void save_to_file();

private:
    Ui::EditScene *ui;
    QString xml_object(SceneObject *obj);
    void fill_obj_list();
};

#endif
