#include <QGuiApplication>

using namespace std;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	const string videoSrcPath {"/dev/video0"};

	QGuiApplication app(argc, argv);
	/* The pipeline must be initilalized after, as the qt controls the event loops.
	 * Also the pipeline must before qml is loaded, because gstreamer loads qmlglsink plugin. */
}
