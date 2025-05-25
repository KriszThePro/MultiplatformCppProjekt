#include "appstyle.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Ui::setupAppStyle(&app);

    MainWindow window;
    window.show();

    return app.exec();
}
