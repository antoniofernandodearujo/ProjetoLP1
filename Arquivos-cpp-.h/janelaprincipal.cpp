#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaPrincipal) {
    ui->setupUi(this);

    QSqlQuery query;

    query.prepare("SELECT * FROM tb_funcionarios");

    if(query.exec()) {

        int cont = 0;
        //quantidade de colunas que eu quero que apareça na tabela
        ui->tableWidgetFuncionarios->setColumnCount(5);
        while(query.next()) {
            ui->tableWidgetFuncionarios->insertRow(cont);
            ui->tableWidgetFuncionarios->setItem(cont, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetFuncionarios->setItem(cont, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetFuncionarios->setItem(cont, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetFuncionarios->setItem(cont, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetFuncionarios->setItem(cont, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetFuncionarios->setRowHeight(cont, 20);
            cont++;
        }

        ui->tableWidgetFuncionarios->setColumnWidth(0,30);
        ui->tableWidgetFuncionarios->setColumnWidth(1, 150);
        ui->tableWidgetFuncionarios->setColumnWidth(3, 130);

        QStringList cabecalhos = {"ID", "Código", "Nome", "Sobrenome", "Função"};
        ui->tableWidgetFuncionarios->setHorizontalHeaderLabels(cabecalhos);
        ui->tableWidgetFuncionarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidgetFuncionarios->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidgetFuncionarios->verticalHeader()->setVisible(false);
        ui->tableWidgetFuncionarios->setStyleSheet("QTableView {selection-background-color: #23444f, color: #fff, font-weight: bold}");
    } else {
        qDebug() << "Error";
    }
}

void JanelaPrincipal::on_pushButtonExcluirFuncionario_clicked() {
    int linha = ui->tableWidgetFuncionarios->currentRow();

    QString funcao = ui->tableWidgetFuncionarios->item(ui->tableWidgetFuncionarios->currentRow(), 4)->text();

    qDebug() << funcao;

    QSqlQuery query;

    query.prepare("DELETE FROM tb_funcionarios WHERE tipo_funcionario='"+funcao+"'");

    if(query.exec()) {
        ui->tableWidgetFuncionarios->removeRow(linha);
        qDebug() << "Excluiu";
    } else {
        qDebug() << query.lastError();
    }

    if(funcao == "Operador" || funcao == "Gerente") {
        query.prepare("DELETE FROM tb_funcionarios WHERE tipo_funcionario='"+funcao+"'");


    } else {
        QMessageBox::information(this, "", "Não pode excluir esse Tipo de Funcionário");
        qDebug() << "Não pode excluir esse Tipo de Funcionário";
    }
}

void JanelaPrincipal::on_pushButtonAddNovoFuncionario_clicked() {
    this->close();

    AdicionarFuncionario add_funcionario;
    add_funcionario.exec();
}

void JanelaPrincipal::removerLinhas(QTableWidget *tw) {
    while(tw->rowCount() > 0) {
        tw->removeRow(0);
    }
}

JanelaPrincipal::~JanelaPrincipal() {
    delete ui;
}

void JanelaPrincipal::on_pushButton_clicked() {

    QString busca;
    removerLinhas(ui->tableWidgetFuncionarios);
    if(ui->lineEdit->text()== "") {
        QMessageBox::information(this, "", "Informe o nome ou parte do nome do funcionário\nOu se preferir filtre pela o cargo na empresa!");
        qDebug() << "Informe o nome ou parte do nome do funcionário\nOu se preferir filtre pela o cargo na empresa!";
    } else {
        busca = ui->lineEdit->text();
    }

    int contL = 0;

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_funcionarios WHERE nome LIKE '%"+busca+"%' ORDER BY nome");

    if(query.exec()) {
        while(query.next()) {
            ui->tableWidgetFuncionarios->insertRow(contL);
            ui->tableWidgetFuncionarios->setItem(contL, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetFuncionarios->setRowHeight(contL, 20);
            contL++;
        }
        ui->lineEdit->clear();
    } else {
        qDebug() << "Erro ao listar funcionários ";
    }

}

void JanelaPrincipal::on_pushButtonFiltrar_clicked() {
    QString busca;
    removerLinhas(ui->tableWidgetFuncionarios);
    if(ui->radioButtonTipoFuncionario->isChecked()) {
        busca = "SELECT * FROM tb_funcionarios ORDER BY tipo_funcionario";
    }

    int contL = 0;

    QSqlQuery query;
    query.prepare(busca);

    if(query.exec()) {
        while(query.next()) {
            ui->tableWidgetFuncionarios->insertRow(contL);
            ui->tableWidgetFuncionarios->setItem(contL, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetFuncionarios->setItem(contL, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetFuncionarios->setRowHeight(contL, 20);
            contL++;

            ui->tableWidgetFuncionarios->selectColumn(4);
        }
        ui->lineEdit->clear();
    } else {
        qDebug() << "Erro ao listar funcionários ";
    }
}

void JanelaPrincipal::on_pushButtonAlterarDadosFuncionario_clicked() {
    this->close();
    int linha = ui->tableWidgetFuncionarios->currentRow();
    int id = ui->tableWidgetFuncionarios->item(linha, 0)->text().toInt();
    EditarFuncionario w_editar(this, id);
    w_editar.exec();
}
