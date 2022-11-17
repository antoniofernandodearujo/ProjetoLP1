#ifndef EDITARFUNCIONARIO_H
#define EDITARFUNCIONARIO_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

#include "janelaprincipal.h"

namespace Ui {
class EditarFuncionario;
}

class EditarFuncionario : public QDialog
{
    Q_OBJECT

public:
    explicit EditarFuncionario(QWidget *parent = nullptr, int id_funcionario = 0);
    ~EditarFuncionario();

private slots:
    void on_pushButtonEditarFunconario_clicked();

private:
    Ui::EditarFuncionario *ui;
};

#endif // EDITARFUNCIONARIO_H
