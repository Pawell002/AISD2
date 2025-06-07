#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[]){

    QApplication app(argc, argv);
    MainWindow okno;
    okno.showMaximized();
    okno.show();
    return app.exec();

}
