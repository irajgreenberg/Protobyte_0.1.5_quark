#include "protocreator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProtoCreator w;
    w.show();

    return a.exec();
}
