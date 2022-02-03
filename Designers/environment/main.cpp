#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <cstdlib>


class Fork : public QProcess {
    public:
    Fork(QStringList argv = QStringList() ) {
        execute("environment", argv); /* Runs this same app as a child. */
    }
    ~Fork() {
        waitForFinished();
    }
};

QTextStream cout(stdout);
int main(int argc, char* argv[]) {

    QCoreApplication qca(argc, argv);
    QStringList al = qca.arguments();
    al.removeAt(0);
    bool fork=al.contains("-f");
    if(fork) {
       int i = al.indexOf("-f");
       al.removeAt(i);
    }

    QProcess process;
    QStringList env = QProcess::systemEnvironment();

    QStringList extraVars;
    if (al.count()  > 0) {
        env << QString("PENGUIN=") + al.first().toUtf8(); // Add an environment variable
        process.setEnvironment(env);
    }

    qDebug() << env;

    if (fork) {
        Fork f;
    }
}

