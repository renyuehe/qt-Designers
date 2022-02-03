#include <QCoreApplication>
#include <QApplication>
#include "logtail.h"
#include <QTextEdit>

//end
//start id=main
int main (int argc, char* argv[]) {
    QApplication app(argc, argv);
    QStringList al = app.arguments();
    QTextEdit textEdit;
    textEdit.setWindowTitle("Debug");
    textEdit.setWindowTitle("logtail demo");
    QString filename;
    if (al.size() > 1) filename = al[1];
    LogTail tail(filename);             /* Create object, starts process too. */
    tail.connect (&tail, SIGNAL(logString(const QString&)),
        &textEdit, SLOT(append(const QString&)));
    textEdit.show();
    return app.exec();
}
//end
