#include "editscene.h"
#include "ui_editscene.h"
#include "sceneobject.h"
#include "scenelight.h"
#include "editlight.h"

#include <QFile>
#include <QFileDialog>
#include <QDir>

QList<SceneObject*> EditScene::objs;
QList<SceneLight*> EditScene::lights;

EditScene::EditScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditScene)
{
    ui->setupUi(this);
    QObject::connect(ui->add_object, SIGNAL(clicked()), this, SLOT(open_object_window()));
    QObject::connect(ui->add_light, SIGNAL(clicked()), this, SLOT(open_light_window()));
    QObject::connect(ui->save_scene, SIGNAL(clicked()), this, SLOT(save_to_file()));
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

void EditScene::open_light_window()
{
    EditLight *win = new EditLight(this);
    win->show();
}

void EditScene::add_object(Ui::EditObject *obj)
{
    SceneObject *scene_obj = new SceneObject(obj);
    objs.append(scene_obj);
    this->ui->object_list->addItem(obj->object_name->text());
}

void EditScene::add_light(Ui::EditLight *light)
{
    SceneLight *scene_light = new SceneLight(light);
    lights.append(scene_light);
    this->ui->object_list->addItem("Light");
}

void EditScene::save_to_file()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Select scene file"), QDir::homePath(), tr("Scene file (*.xml)"));
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream <<
            "<scene>"
                  "<config>"
                      "<ambient>"<< ui->ambient->value() <<"</ambient>";
                    if (ui->filter->currentText() == "sepia")
                        stream << "<filter> sepia </filter>";
                    else if (ui->filter->currentText() == "Black & White")
                        stream << "<filter> B&W </filter>";
                    else
                        stream << "<filter></filter>";
                   stream <<
                  "</config>"
                  "<camera>"
                          "<position>"
                              "<x>"<< ui->pos_x->value() <<"</x>"
                              "<y>"<< ui->pos_y->value() <<"</y>"
                              "<z>"<< ui->pos_z->value() <<"</z>"
                          "</position>"
                          "<angle>"
                              "<x>"<< ui->angle_x->value() <<"</x>"
                              "<y>"<< ui->angle_y->value() <<"</y>"
                              "<z>"<< ui->angle_z->value() <<"</z>"
                          "</angle>"
                          "<fov>"<< ui->fov->value() <<"</fov>"
                  "</camera>"
            "<lights>";
        for (int i = 0; i < lights.size(); ++i) {
          stream << xml_light(lights.at(i)) << endl;
        }
            stream <<
                "</lights>"
            "<objects>";
        for (int i = 0; i < objs.size(); ++i) {
          stream << xml_object(objs.at(i)) << endl;
        }
        stream <<
             "</objects>"
             "</scene>" << endl;

    }
}

QString EditScene::xml_light(SceneLight *light)
{
    QString object;
    QTextStream(&object) <<
        "<light>"
             "<position>"
                "<x>"<< light->pos_x <<"</x>"
                "<y>"<< light->pos_y <<"</y>"
                "<z>"<< light->pos_z <<"</z>"
            "</position>"
            "<intensity>"<< light->intensity <<"</intensity>"
            "<color>"
                "<r>"<< light->col_r <<"</r>"
                "<g>"<< light->col_g <<"</g>"
                "<b>"<< light->col_b <<"</b>"
            "</color>"
        "</light>";
    return (object);
}

QString EditScene::xml_object(SceneObject *obj)
{
    QString object;

    QTextStream(&object) <<
        "<" << obj->object_name.toLower() << ">"
         "<position>"
            "<x>"<< QString::number(obj->pos_x) <<"</x>"
            "<y>"<< QString::number(obj->pos_y) <<"</y>"
            "<z>"<< QString::number(obj->pos_z) <<"</z>"
        "</position>"
        "<radius>"<< obj->radius <<"</radius>"
        "<radius2>"<< obj->radius_2 <<"</radius2>"
        "<angle>"<< obj->angle <<"</angle>"
         "<normal>"
             "<x>"<< obj->norm_x <<"</x>"
             "<y>"<< obj->norm_y <<"</y>"
             "<z>"<< obj->norm_z <<"</z>"
         "</normal>"
        "<direction>"
            "<x>"<< obj->dir_x <<"</x>"
            "<y>"<< obj->dir_y <<"</y>"
            "<z>"<< obj->dir_z <<"</z>"
        "</direction>"
        "<mat>"
            "<color>"
                "<r>"<< obj->col_r <<"</r>"
                "<g>"<< obj->col_g <<"</g>"
                "<b>"<< obj->col_b <<"</b>"
            "</color>"
        "</mat>"
        "</" << obj->object_name.toLower() << ">";
    return (object);
}
