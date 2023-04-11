#include "gallery.h"
#include "scenemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path;

    auto arguments = a.arguments();
    if(arguments.size() > 1){
        path = arguments[1];
    }

    SceneManager sceneManager;
    Gallery w{sceneManager};

    if(!path.isEmpty())
        w.openImage(path);

    w.show();

    return a.exec();
}
