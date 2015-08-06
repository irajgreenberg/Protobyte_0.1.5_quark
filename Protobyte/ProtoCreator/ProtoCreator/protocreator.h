#ifndef PROTOCREATOR_H
#define PROTOCREATOR_H

#include <QMainWindow>

namespace Ui {
class ProtoCreator;
}

class ProtoCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProtoCreator(QWidget *parent = 0);
    ~ProtoCreator();

private:
    Ui::ProtoCreator *ui;
};

#endif // PROTOCREATOR_H
