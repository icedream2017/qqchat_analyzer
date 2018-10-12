#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>
#include <QTime>
#include "database.h"

#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

class TextProcessor : public QThread
{
    Q_OBJECT
public:
    TextProcessor();
    TextProcessor(QString);
    void run();
    int getFileLength();
    void preprocess();
    void disposeDateTime();
    QString getContent();
    void disposeInfo(QString);
    void initTable();
    static QString getQQNum(QString);
    void setDB(Database*);

private:
    QString filename;
    int fileLength;
    Database *mydb;
    QString cache;
    QString result;
    QString res1;
    QString res2;
    QString res3;
    QStringList header;
    int cid;
    bool flag;
    QString date;
    QString time;
    QString username;
    QString account;
    QString message;

signals:
    void filePos(int);
    void process_fin();
};

#endif // TEXTPROCESSOR_H
