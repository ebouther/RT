#ifndef EDITLIGHT_H
#define EDITLIGHT_H

#include <QDialog>

namespace Ui {
class EditLight;
}

class EditLight : public QDialog
{
    Q_OBJECT

public:
    explicit EditLight(QWidget *parent = 0);
    ~EditLight();

public slots:
        void add_light();

private:
    Ui::EditLight *ui;

    QWidget *parent;
};

#endif // EDITLIGHT_H
