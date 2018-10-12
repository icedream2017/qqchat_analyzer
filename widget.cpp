#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initDB();
    ui->progressBar->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initDB()
{
    this->mydb = new Database();
    if(!(mydb->openDataBase("msg.db")))
    {
        QMessageBox::warning(this,"Database Error","Open system database error.\nPlease repair or reinstall program.",QMessageBox::Ok);
        this->close();
    }

}

void Widget::setPagesAvail(bool b)
{
    ui->tab_2->setEnabled(b);
    ui->tab_3->setEnabled(b);
    ui->tab_4->setEnabled(b);
}

void Widget::received_filePos(int pos)
{
    ui->progressBar->setValue(pos);
}

void Widget::on_pushButton_browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("打开文件"),"./",tr("文本文档 (*.txt)"));
    if(!filename.isEmpty()) {
        ui->lineEdit_file->setText(filename);
        ui->pushButton_read->setEnabled(true);
        ui->pushButton_read->setText(tr("开始导入"));
    }

}

void Widget::process_finished()
{
    ui->pushButton_browse->setEnabled(true);
    ui->lineEdit_file->setEnabled(true);
    ui->pushButton_read->setText(tr("导入完成"));
    this->setPagesAvail(true);
//    ui->textEdit_content->setText(ps->getContent());
}

void Widget::on_pushButton_read_clicked()
{
    QString filename = ui->lineEdit_file->text();
    if(!filename.isEmpty()) {
        ui->pushButton_read->setEnabled(false);
        ui->pushButton_browse->setEnabled(false);
        ui->lineEdit_file->setEnabled(false);
//        ui->textEdit_content->clear();
        this->setPagesAvail(false);
        ui->pushButton_read->setText(tr("处理中..."));
        ui->progressBar->setVisible(true);
        this->ps = new TextProcessor(filename);
        connect(ps,SIGNAL(filePos(int)),this,SLOT(received_filePos(int)));
        connect(ps,SIGNAL(process_fin()),this,SLOT(process_finished()));
        ps->setDB(this->mydb);
        ps->start();
    }
}

void Widget::on_pushButton_search_content_clicked()
{
    this->an = new TextAnalyzer();
    ui->tableView_search->resizeColumnsToContents();
    ui->tableView_search->setModel(an->searchFunction(ui->lineEdit_search->text(), 0));
    ui->tableView_search->show();
}

void Widget::on_pushButton_search_user_clicked()
{
    this->an = new TextAnalyzer();
    ui->tableView_search->resizeColumnsToContents();
    ui->tableView_search->setModel(an->searchFunction(ui->lineEdit_search->text(), 1));
    ui->tableView_search->show();
}

void Widget::on_pushButton_ana_1_clicked()
{
    this->an = new TextAnalyzer();
    ui->tableView_search->resizeColumnsToContents();
    ui->tableView_analyze->setModel(an->analyzeFunction(NULL, 0));
    ui->tableView_analyze->show();
}

void Widget::on_pushButton_ana_2_clicked()
{
    this->an = new TextAnalyzer();
    ui->tableView_search->resizeColumnsToContents();
    ui->tableView_analyze->setModel(an->analyzeFunction(ui->lineEdit_ana_1->text(), 1));
    ui->tableView_analyze->show();
}
