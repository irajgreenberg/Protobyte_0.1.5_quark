#ifndef PROTOCREATOR_H
#define PROTOCREATOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDirIterator>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <iostream>

namespace Ui {
class ProtoCreator;
}

class ProtoCreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProtoCreator(QWidget *parent = 0);
    ~ProtoCreator();

private slots:
    void on_runButton_clicked();

private:
    Ui::ProtoCreator *ui;

    QString slnString;

    void runScript(const QString& usrProjName);
    void print(const QString& myString);
    void setSlnString(const QString& usrProjName);
};

#endif // PROTOCREATOR_H
