#include "textanalyzer.h"

TextAnalyzer::TextAnalyzer()
{
}

QSqlQueryModel* TextAnalyzer::analyzeFunction(QString keyword, int mode=0)
{
    QString sql_1 = "select c_name,count(c_name) as c_count from chatmsg group by c_name order by c_count desc";
    QString sql_2 = "select strftime('%H',c_time) as c_hr,count(c_name) as c_count from chatmsg where c_name='"+keyword+"' group by c_hr";
    switch(mode) {
    case 0:
        this->query = new QSqlQuery();
        this->model = new QSqlQueryModel();
        this->query->exec(sql_1);
        this->model->setQuery(*query);
        this->model->setHeaderData(0, Qt::Horizontal, "QQ/用户名");
        this->model->setHeaderData(1, Qt::Horizontal, "消息数量");
        return this->model;
        break;
    case 1:
        this->query = new QSqlQuery();
        this->model = new QSqlQueryModel();
        this->query->exec(sql_2);
        this->model->setQuery(*query);
        this->model->setHeaderData(0, Qt::Horizontal, "时间");
        this->model->setHeaderData(1, Qt::Horizontal, "消息数量");
        return this->model;
        break;
    default:
        return NULL;
    }
}

QSqlQueryModel* TextAnalyzer::searchFunction(QString keyword, int mode=0)
{
    QString sql_1 = "select * from chatmsg where c_msg like '%"+keyword+"%';";
    QString sql_2 = "select * from chatmsg where c_name='"+keyword+"';";
    switch(mode) {
    case 0:
        this->query = new QSqlQuery();
        this->model = new QSqlQueryModel();
        this->query->exec(sql_1);
        this->model->setQuery(*query);
        this->model->setHeaderData(0, Qt::Horizontal, "序号");
        this->model->setHeaderData(1, Qt::Horizontal, "日期");
        this->model->setHeaderData(2, Qt::Horizontal, "时间");
        this->model->setHeaderData(3, Qt::Horizontal, "用户");
        this->model->setHeaderData(4, Qt::Horizontal, "消息");
        return this->model;
        break;
    case 1:
        this->query = new QSqlQuery();
        this->model = new QSqlQueryModel();
        query->exec(sql_2);
        this->model->setQuery(*query);
        this->model->setHeaderData(0, Qt::Horizontal, "序号");
        this->model->setHeaderData(1, Qt::Horizontal, "日期");
        this->model->setHeaderData(2, Qt::Horizontal, "时间");
        this->model->setHeaderData(3, Qt::Horizontal, "用户");
        this->model->setHeaderData(4, Qt::Horizontal, "消息");
        return this->model;
        break;
    default:
        return NULL;
    }
}

QSqlQueryModel* TextAnalyzer::compareFunction(QString k1, QString k2)
{
    QString sql =
}
