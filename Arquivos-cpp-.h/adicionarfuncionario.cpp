#include "adicionarfuncionario.h"
#include "janelaprincipal.h"
#include "ui_adicionarfuncionario.h"

AdicionarFuncionario::AdicionarFuncionario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdicionarFuncionario) {
    ui->setupUi(this);

    ui->radioButtonOperador->setChecked(true);
    ui->lineEditCodigo->setFocus();
    ui->lineEditCodigo->isClearButtonEnabled();
    ui->lineEditCodigo->isClearButtonEnabled();
    ui->lineEditNome->isClearButtonEnabled();
    ui->lineEditSobrenome->isClearButtonEnabled();
    ui->lineEditEndereco->isClearButtonEnabled();
    ui->lineEditNumCasa->isClearButtonEnabled();
    ui->lineEditNumTelefone->isClearButtonEnabled();
    ui->lineEditDataIngresso->isClearButtonEnabled();
    ui->lineEditAreaDeSupervisaoGerente->isClearButtonEnabled();
    ui->lineEditAreaDeSupervisaoDiretor->isClearButtonEnabled();
    ui->lineEditAreaDeFormacaoDiretor->isClearButtonEnabled();
    ui->lineEditAreaDeFormacaoPresidente->isClearButtonEnabled();
}

void AdicionarFuncionario::on_pushButtonAddNovouncionario_clicked() {
    QString codigo = ui->lineEditCodigo->text();
    QString nome = ui->lineEditNome->text();
    QString sobrenome = ui->lineEditSobrenome->text();
    QString endereco = ui->lineEditEndereco->text();
    QString numCasa = ui->lineEditNumCasa->text();
    QString numTelefone = ui->lineEditNumTelefone->text();
    QString dataIngresso = ui->lineEditDataIngresso->text();

    QString tipoFuncionario = "";

    QString areaDeSupervisaoGerenteTxt = ui->lineEditAreaDeSupervisaoGerente->text();
    QString areaDeSupervisaoDiretorTxt = ui->lineEditAreaDeSupervisaoDiretor->text();
    QString areaDeFormacaoDiretorTxt = ui->lineEditAreaDeFormacaoDiretor->text();
    QString areaDeFormacaoPresidenteTxt = ui->lineEditAreaDeFormacaoPresidente->text();
    QString formacaoMaximaDoPresidenteTxt = ui->comboBoxFormacaoMAxima->currentText();

    if(ui->radioButtonOperador->isChecked()) {
        tipoFuncionario = ui->radioButtonOperador->text();
    } else if(ui->radioButtonGerente->isChecked()) {
        tipoFuncionario = ui->radioButtonGerente->text();
    } else if(ui->radioButtonDiretor->isChecked()) {
        tipoFuncionario = ui->radioButtonDiretor->text();
    } else if(ui->radioButtonPresidente->isChecked()) {
        tipoFuncionario = ui->radioButtonPresidente->text();
    }

    if(codigo == "" || nome == "" || sobrenome == "" || endereco == "" ||
       numCasa == "" || numTelefone == "" || dataIngresso == "" || tipoFuncionario == "") {
        QMessageBox::warning(this, "Campos Vazios", "Por favor Preencha os Campos Iniciais");

        ui->lineEditCodigo->clear();
        ui->lineEditNome->clear();
        ui->lineEditSobrenome->clear();
        ui->lineEditEndereco->clear();
        ui->lineEditNumCasa->clear();
        ui->lineEditNumTelefone->clear();
        ui->lineEditDataIngresso->clear();

        ui->lineEditCodigo->setFocus();

    } else {

        QSqlQuery query;

        query.prepare("insert into tb_funcionarios (codigo_nome, sobrenome, endereco, numero_casa, numero_telefone, data_ingresso, tipo_funcionario, area_formacao, area_supervisao, formacao_maxima) values(:codigo_func, :nome, :sobrenome, :endereco, :numero_casa, :numero_telefone, :data_ingresso, :tipo_funcionario, :area_formacao, :area_supervisao, :formacao_maxima)");

        query.bindValue(":codigo_func", codigo);
        query.bindValue(":nome", nome);
        query.bindValue(":sobrenome", sobrenome);
        query.bindValue(":endereco", endereco);
        query.bindValue(":numero_casa", numCasa);
        query.bindValue(":numero_telefone", numTelefone);
        query.bindValue(":data_ingresso", dataIngresso);
        query.bindValue(":tipo_funcionario", tipoFuncionario);

        if(ui->radioButtonDiretor->isChecked() && areaDeSupervisaoDiretorTxt != "" && areaDeFormacaoDiretorTxt != "") {
             query.bindValue(":area_formacao", areaDeFormacaoDiretorTxt);
             query.bindValue(":area_supervisao", areaDeSupervisaoDiretorTxt);
             query.bindValue(":formacao_maxima", "");
        }

        if(ui->radioButtonGerente->isChecked() && areaDeSupervisaoGerenteTxt != "") {
            query.bindValue(":area_formacao", "");
            query.bindValue(":area_supervisao", areaDeSupervisaoGerenteTxt);
            query.bindValue(":formacao_maxima", "");
        }

        if(ui->radioButtonPresidente->isChecked() && areaDeFormacaoPresidenteTxt != "" && formacaoMaximaDoPresidenteTxt != "-- Escolha --") {
            query.bindValue(":area_formacao", areaDeFormacaoPresidenteTxt);
            query.bindValue(":area_supervisao", "");
            query.bindValue(":formacao_maxima", formacaoMaximaDoPresidenteTxt);
        }

        if(query.exec()) {
            qDebug() << "Registro gravado com sucesso!";
            QMessageBox::information(this, "", "Funcionário Cadastrado com SUCESSO!");
            ui->lineEditCodigo->clear();
            ui->lineEditNome->clear();
            ui->lineEditSobrenome->clear();
            ui->lineEditEndereco->clear();
            ui->lineEditNumCasa->clear();
            ui->lineEditNumTelefone->clear();
            ui->lineEditDataIngresso->clear();

            ui->lineEditCodigo->setFocus();
        } else {
            QMessageBox::critical(this, "", "Funcionário Não Cadastrado com SUCESSO!");
            qDebug() << "Erro ao inserir registro";
        }
    }
}

void AdicionarFuncionario::on_pushButtonVoltar_clicked() {

    this->close();

    JanelaPrincipal w_principal;
    w_principal.exec();
}

AdicionarFuncionario::~AdicionarFuncionario() {
    delete ui;
}
