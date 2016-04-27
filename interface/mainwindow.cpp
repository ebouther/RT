#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->b_render_scene, SIGNAL(clicked()), this, SLOT(render_scene()));
    QObject::connect(ui->b_edit_scene, SIGNAL(clicked()), this, SLOT(open_edit_window()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::render_scene()
{
    QProcess rt;
    rt.start("/nfs/2015/e/ebouther/Programming/RT/rtv1", QStringList() << "/nfs/2015/e/ebouther/Programming/RT/scenes/demo.xml");
    if (!rt.waitForStarted())
        return 0;
    if (!rt.waitForFinished())
        return 0;
    return 1;
}

void MainWindow::open_edit_window()
{
    EditScene *win = new EditScene();
    win->show();
}
