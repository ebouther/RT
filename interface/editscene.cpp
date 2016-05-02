#include "editscene.h"
#include "ui_editscene.h"
#include "sceneobject.h"

#include <QFile>
#include <QDebug>

QList<SceneObject*> EditScene::objs;

EditScene::EditScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditScene)
{

    ui->setupUi(this);
    QObject::connect(ui->add_object, SIGNAL(clicked()), this, SLOT(open_object_window()));
    QObject::connect(ui->save_scene, SIGNAL(clicked()), this, SLOT(save_to_file()));
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
    objs.append(scene_obj);
    this->ui->object_list->addItem(obj->object_name->text());
}

void EditScene::save_to_file()
{
    QFile::remove("/nfs/2015/e/ebouther/Programming/RT/scene.xml");
    QString filename="/nfs/2015/e/ebouther/Programming/RT/scene.xml";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream <<
            "<scene>"
                  "<config>"
                      "<ambient> 0.2 </ambient>"
                      "<filter> sepia </filter>"
                  "</config>"
                  "<camera>"
                          "<position>"
                              "<x> 0.0 </x>"
                              "<y> 0.0 </y>"
                              "<z> 0.0 </z>"
                          "</position>"

                          "<angle>"
                              "<x> 0.0 </x>"
                              "<y> 0.0 </y>"
                              "<z> 0.0 </z>"
                          "</angle>"
                          "<fov> 70.0 </fov>"
                  "</camera>"
                  "<lights>"
                      "<light>"
                          "<intensity> 0.3 </intensity>"
                          "<position>"
                              "<x> 40.0 </x>"
                              "<y>  0.0 </y>"
                              "<z> 20.0 </z>"
                          "</position>"
                          "<color>"
                              "<r> 1.0 </r>"
                              "<g> 1.0 </g>"
                              "<b> 1.0 </b>"
                          "</color>"
                      "</light>"
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

QString EditScene::xml_object(SceneObject *obj)
{
    QString object;
    QTextStream(&object) <<
        "<" << obj->object_name.toLower() << ">"
         "<position>"
            "<x> 20.0 </x>"
            "<y>  0.0 </y>"
            "<z> 80.0 </z>"
        "</position>"
        "<radius> 10.0 </radius>"
        "<normal>"
            "<x> 0.0 </x>"
            "<y> 1.0 </y>"
            "<z> 0.0 </z>"
        "</normal>"
        "<mat>"
            "<color>"
                "<r> 0.0 </r>"
                "<g> 0.5 </g>"
                "<b> 0.0 </b>"
            "</color>"
        "</mat>"
        "</" << obj->object_name.toLower() << ">";
    return (object);
}
