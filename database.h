#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    Database();
    ~Database();
    bool openDataBase(QString dbname);

    QSqlDatabase db;
};

#endif // DATABASE_H
