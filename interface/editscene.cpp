#include "editscene.h"
#include "ui_editscene.h"
#include "sceneobject.h"

QList<SceneObject*> EditScene::objs;

EditScene::EditScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditScene)
{

    ui->setupUi(this);
    QObject::connect(ui->add_object, SIGNAL(clicked()), this, SLOT(open_object_window()));
    //this->fill_obj_list();
}

EditScene::~EditScene()
{
    delete ui;
}

void EditScene::open_object_window()
{
    SelectObject *win = new SelectObject(this);
    win->show();
}

void EditScene::add_object(Ui::EditObject *obj)
{
    SceneObject *scene_obj = new SceneObject(obj);
    EditScene::ui->
}
