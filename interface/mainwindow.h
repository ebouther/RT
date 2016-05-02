#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QString>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    int render_scene();
    void open_edit_window();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
