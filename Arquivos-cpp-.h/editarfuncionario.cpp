#include "editarfuncionario.h"
#include "ui_editarfuncionario.h"

static int id;

EditarFuncionario::EditarFuncionario(QWidget *parent, int id_funcionario) :
    QDialog(parent),
    ui(new Ui::EditarFuncionario) {
    ui->setupUi(this);

    ui->lineEditCodigo->setClearButtonEnabled(true);
    ui->lineEditNome->setClearButtonEnabled(true);
    ui->lineEditSobrenome->setClearButtonEnabled(true);
    ui->lineEditEndereco->setClearButtonEnabled(true);
    ui->lineEditNumCasa->setClearButtonEnabled(true);
    ui->lineEditNumTelefone->setClearButtonEnabled(true);
    ui->lineEditDataIngresso->setClearButtonEnabled(true);
    ui->lineEditAreaDeSupervisaoGerente->setClearButtonEnabled(true);
    ui->lineEditAreaDeSupervisaoDiretor->setClearButtonEnabled(true);
    ui->lineEditAreaDeFormacaoDiretor->setClearButtonEnabled(true);
    ui->lineEditAreaDeFormacaoPresidente->setClearButtonEnabled(true);

    id = id_funcionario;
    QSqlQuery query;
    query.prepare("select * from tb_funcionarios where id="+QString::number(id_funcionario));
    if(query.exec()) {
        query.first();
        ui->lineEditCodigo->setText(query.value(1).toString());
        ui->lineEditNome->setText(query.value(2).toString());
        ui->lineEditSobrenome->setText(query.value(3).toString());
        if(query.value(4).toString() == "Operador") {
            ui->radioButtonOperador->setChecked(true);
        } else if(query.value(4).toString() == "Gerente") {
            ui->radioButtonGerente->setChecked(true);
            ui->lineEditAreaDeSupervisaoGerente->setText(query.value(10).toString());
        } else if(query.value(4).toString() == "Diretor") {
            ui->radioButtonDiretor->setChecked(true);
            ui->lineEditAreaDeFormacaoDiretor->setText(query.value(9).toString());
            ui->lineEditAreaDeSupervisaoDiretor->setText(query.value(10).toString());
        } else {
            ui->radioButtonPresidente->setChecked(true);
            ui->lineEditAreaDeFormacaoPresidente->setText(query.value(9).toString());
            ui->comboBoxFormacaoMAxima->currentText();
        }

        ui->lineEditEndereco->setText(query.value(5).toString());
        ui->lineEditNumCasa->setText(query.value(6).toString());
        ui->lineEditNumTelefone->setText(query.value(7).toString());
        ui->lineEditDataIngresso->setText(query.value(8).toString());
    } else {
        qDebug() << "Erro ao selecionar funcionário";
    }

}

void EditarFuncionario::on_pushButtonEditarFunconario_clicked() {
    QString codigo = ui->lineEditCodigo->text();
    QString nome = ui->lineEditNome->text();
    QString sobrenome = ui->lineEditSobrenome->text();
    QString endereco = ui->lineEditEndereco->text();
    QString numCasa = ui->lineEditNumCasa->text();
    QString numTelefone = ui->lineEditNumTelefone->text();
    QString dataIngresso = ui->lineEditDataIngresso->text();

    QString tipoFuncionario = "";
    QString vazio="";

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

    QSqlQuery query;

    QString idMuda = QString::number(id);

    query.prepare("update tb_funcionarios set codigo_func='"+codigo+"', nome='"+nome+"', sobrenome='"+sobrenome+"', endereco='"+endereco+"', numero_casa='"+numCasa+"', numero_telefone='"+numTelefone+"', data_ingresso='"+dataIngresso+"', tipo_funcionario='"+tipoFuncionario+"' where id='"+idMuda+"'");

    if(query.exec()) {
        QMessageBox::information(this, "", "Dados Alterados Com Sucesso");
        this->close();
        JanelaPrincipal w_principal;
        w_principal.exec();
        qDebug() << "Dados Alterados com sucesso";
    } else {
        qDebug() << "Não foi possível atualizar o funcionário";
        qDebug() << query.lastError();
    }
}

EditarFuncionario::~EditarFuncionario() {
    delete ui;
}
