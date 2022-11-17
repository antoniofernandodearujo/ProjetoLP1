#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    bd = QSqlDatabase::addDatabase("QSQLITE");

    QString dir = qApp->applicationDirPath();
    QString banco = dir+"/bd/funcionarios.db";

    bd.setDatabaseName(banco);

    if(!bd.open()) {
      qDebug() << "Não foi possível abrir o banco de dados: "+banco;
    } else {
        qDebug() << "Banco de dados aberto com SUCESSO!";
    }

    //adicionandos algumas fucionalidades nos inputs
    ui->lineEditUserName->setClearButtonEnabled(true);
    ui->lineEditPassword->setClearButtonEnabled(true);

    ui->lineEditUserName->setFocus();

}

void MainWindow::on_pushButtonLogin_clicked() {
    QString user = ui->lineEditUserName->text();
    QString pass = ui->lineEditPassword->text();

    if(!bd.isOpen()) {
        qDebug() << "Banco de Dados não estar aberto!";
        return;
    }

    QSqlQuery query;

    query.prepare("select * from tb_login where username='"+user+"' and password='"+pass+"'");

    if(query.exec()) {
        int cont = 0;
        qDebug() << "Funcionou";

        while(query.next()) {
            cont++;
        }

        if(cont > 0) {
            this->close();
            JanelaPrincipal w_principal;
            w_principal.setModal(true);
            w_principal.exec();
        } else {
            qDebug() << "Login Não efetuado";
            QMessageBox::warning(this, "Login não efetuado", "Username e/ou Password INCORRETOS!");
            ui->lineEditUserName->clear();
            ui->lineEditPassword->clear();
            ui->lineEditUserName->setFocus();
        }

    } else {
        qDebug() << query.lastError();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}


