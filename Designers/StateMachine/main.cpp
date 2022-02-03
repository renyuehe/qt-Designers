#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QPauseAnimation>
#include <QAnimationGroup>

int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    QPushButton *button = new QPushButton("Animated Button");
    button->setPalette(QPalette(Qt::red));
    button->show();

    //创建状态机
    QStateMachine *machine = new QStateMachine;
    //QState *state1 = new QState(machine->rootState());
    //状态一
    QState *state1 = new QState(machine);
    state1->assignProperty(button, "geometry", QRect(0, 0, 150, 30));
    state1->assignProperty(button, "palette", QPalette(Qt::red));

    machine->setInitialState(state1);
    //QState *state2 = new QState(machine->rootState());
    //状态二
    QState *state2 = new QState(machine);
    state2->assignProperty(button, "geometry", QRect(250, 250, 150, 30));
    state2->assignProperty(button, "palette", QPalette(Qt::green));

    //
    QSignalTransition *transition1 = state1->addTransition(button,
                                                           SIGNAL(clicked()), state2);
    transition1->addAnimation(new QPropertyAnimation(button, "geometry"));
    transition1->addAnimation(new QPropertyAnimation(button, "palette"));

    QSignalTransition *transition2 = state2->addTransition(button,
                                                           SIGNAL(clicked()), state1);
    transition2->addAnimation(new QPropertyAnimation(button, "geometry"));
    transition2->addAnimation(new QPropertyAnimation(button, "palette"));
    machine->start();

    app.exec();
}
