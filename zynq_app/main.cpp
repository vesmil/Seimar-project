#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filename="test.txt";
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "test test\n";
        file.close();
   }

    return a.exec();
}
