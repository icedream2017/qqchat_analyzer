#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "textprocessor.h"
#include "textanalyzer.h"
#include "database.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initDB();

private slots:
    void received_filePos(int);

    void process_finished();

    void on_pushButton_browse_clicked();

    void on_pushButton_read_clicked();

    void on_pushButton_search_content_clicked();

    void on_pushButton_search_user_clicked();

    void on_pushButton_ana_1_clicked();

    void on_pushButton_ana_2_clicked();

private:
    Ui::Widget *ui;
    Database *mydb;
    TextProcessor *ps;
    TextAnalyzer *an;
    void setPagesAvail(bool);
};

#endif // WIDGET_H
