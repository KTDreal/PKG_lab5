
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon("crop-tool.png"));
    w.setWindowTitle("Cutting off segments");
    w.show();
    return a.exec();
}
