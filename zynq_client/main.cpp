#include <QApplication>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("gst-pipeline: udpsrc port=\"9002\" "
                          "caps = \"application/x-rtp, media=(string)video, width=(string)1024, framerate=(fraction)60/1, height=(string)768, format=(string)RGB\" "
                          "! rtpvrawdepay ! queue ! videoconvert ! autovideosink"));

    player->play();

    return a.exec();
}
