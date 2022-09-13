#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>

#include <graphic/menu/menubuilder.h>

#include "library/visible/gstreamer/gsfacade.h"
#include "library/visible/visca/visca.h"
#include "global/config.h"
#include "graphic/mainWindow.h"

void nonEssentialSetup()
{
    qSetMessagePattern("(%{category}) %{function} - %{message}");
}

int main(int argc, char *argv[])
{
    nonEssentialSetup();

    QApplication a(argc, argv);

    // Setup gstreamer pipelines from cam
    GsFacade gsFacade{};
    // gsFacade.initAndStart(GsFacade::WIRIS_RTP); // | GsFacade::RAW_DISPLAY

    Visca visca(glb::path::CAMERA_UART.c_str());

    Controller controller(visca, gsFacade);

    // Create UI
    Menu &menu = Menu::getInstance();
    MenuBuilder::buildMenuTree(menu.m_root.get(), static_cast<QWidget*>(&menu), &controller);

    menu.show();

    return a.exec();
}
