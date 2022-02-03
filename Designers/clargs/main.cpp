
#if 0 //c++版 接受main参数
#include <iostream>
#include <cstdlib>  /* for atoi() */

int main (int argc, char* argv[]) {
    using namespace std;
    cout << "argc = " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << "argv# " << i << " is " << argv[i] << endl;
    }
    int num = atoi(argv[argc - 1]);
    cout << num * 2 << endl;
    return 0;
}

#elif 1 //Qt版 接受main参数
#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

int main (int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QTextStream cout(stdout);
    QStringList arglst = app.arguments();
    cout << "argc = " << argc << endl;
    for (int i=0; i<arglst.size(); ++i) {
        cout << QString("argv#%1 is %2").arg(i).arg(arglst[i]) << endl;
    }
    int num = arglst[argc - 1].toInt();
    cout << num * 2 << endl;
}
#endif

