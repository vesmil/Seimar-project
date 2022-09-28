#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>

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

    Menu &menu = Menu::getInstance();
    menu.show();

    GsFacade gsFacade{};    // No stream starts by default, if you want - gsFacade.initAndStart(GsFacade::WIRIS_RTP | GsFacade::RAW_DISPLAY);

    Visca visca(Settings::getInstance().path.cameraUart.c_str());

    Controller controller(visca, gsFacade);
    MenuBuilder::buildMenuTree(menu, &controller);

    return a.exec();
}
