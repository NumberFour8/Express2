#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "window.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();

    return a.exec();
}
