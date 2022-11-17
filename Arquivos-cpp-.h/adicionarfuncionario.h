#ifndef ADICIONARFUNCIONARIO_H
#define ADICIONARFUNCIONARIO_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class AdicionarFuncionario;
}

class AdicionarFuncionario : public QDialog
{
    Q_OBJECT

public:
    explicit AdicionarFuncionario(QWidget *parent = nullptr);
    ~AdicionarFuncionario();

private slots:
    void on_pushButtonAddNovouncionario_clicked();

    void on_pushButtonVoltar_clicked();

private:
    Ui::AdicionarFuncionario *ui;
};

#endif // ADICIONARFUNCIONARIO_H
