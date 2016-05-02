#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editscene.h"

#include <QDir>
#include <QFileDialog>

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
    QProcess rt_process;
    QString rt_bin = QFileDialog::getOpenFileName(this,
        tr("Select rtv1 binary"), QDir::homePath(), tr("Rtv1 binary (rtv1)"));
    QFileInfo rt_path(rt_bin);
    rt_process.start(rt_bin, QStringList() << rt_path.absoluteDir().absolutePath() + "/scene.xml");
    if (!rt_process.waitForStarted())
        return 0;
    if (!rt_process.waitForFinished())
        return 0;
    return 1;
}

void MainWindow::open_edit_window()
{
    EditScene *win = new EditScene();
    win->show();
}
