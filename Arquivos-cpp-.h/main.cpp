#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <windows.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    QSplashScreen *telaSplash = new QSplashScreen();

    telaSplash->setPixmap(QPixmap(":/telaSplah/assets/splash-arrendodado (1).png"));

    telaSplash->show();

    Qt::Alignment alignTexts = Qt::AlignAbsolute | Qt::AlignTop;

    telaSplash->showMessage("Carregando...", alignTexts, Qt::white);
    Sleep(1000);
    telaSplash->showMessage("Carregando módulos...", alignTexts, Qt::white);
    Sleep(1000);
    telaSplash->showMessage("Carregando o Banco de Dados...", alignTexts, Qt::white);
    Sleep(1000);
    telaSplash->showMessage("", alignTexts, Qt::white);
    Sleep(1000);
    telaSplash->showMessage("Terminando Conexões com o Banco de Dados...", alignTexts, Qt::white);
    Sleep(1000);

    QTimer::singleShot(5000, telaSplash, SLOT(close()));
    QTimer::singleShot(5000, &w, SLOT(show()));

    //w.show();
    return a.exec();
}
