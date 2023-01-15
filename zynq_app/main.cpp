#include <QApplication>

#include "graphic/menu/menu.h"
#include "graphic/mainwindow.h"
#include "graphic/menu/menubuilder.h"
#include "library/application/settings.h"

#include "library/visible/gstreamer/gsfacade.h"
#include "library/visible/visca/visca.h"

void nonEssentialSetup()
{
    qSetMessagePattern("(%{category}) %{function} - %{message}");
}

int main(int argc, char *argv[])
{
    nonEssentialSetup();

    QApplication a(argc, argv);

    // Menu::getInstance().show();
    MainWindow main;
    main.show();

    GsFacade gsFacade{};

    Visca visca(Settings::getInstance().path.cameraUart.c_str());

    Controller controller(visca, gsFacade);
    MenuBuilder::buildMenuTree(Menu::getInstance(), &controller);

    return a.exec();
}
