#include <QApplication>
#include "platform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
	print("hello world");
    return a.exec();
}
