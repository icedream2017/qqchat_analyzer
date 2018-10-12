#include "database.h"

Database::Database()
{
}

Database::~Database()
{
    db.close();
}

bool Database::openDataBase(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    return db.open();
}
