#include <QString>
#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

class TextAnalyzer
{
public:
    TextAnalyzer();
    QSqlQueryModel* searchFunction(QString,int);
    QSqlQueryModel* analyzeFunction(QString,int);
    QSqlQueryModel* compareFunction(QString,QString);

private:
    QString file;
    QSqlQuery *query;
    QSqlQueryModel *model;
};

#endif // TEXTANALYZER_H
