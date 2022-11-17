#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QDialog>
#include "adicionarfuncionario.h"
#include "editarfuncionario.h"
#include <QDebug>
#include <QtSql>
#include <QTableWidget>

namespace Ui {
class JanelaPrincipal;
}

class JanelaPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaPrincipal(QWidget *parent = nullptr);
    ~JanelaPrincipal();
    void removerLinhas(QTableWidget *tw);

private slots:

    void on_pushButtonAddNovoFuncionario_clicked();

    void on_pushButtonExcluirFuncionario_clicked();

    void on_pushButton_clicked();

    void on_pushButtonFiltrar_clicked();

    void on_pushButtonAlterarDadosFuncionario_clicked();

private:
    Ui::JanelaPrincipal *ui;
};

#endif // JANELAPRINCIPAL_H
