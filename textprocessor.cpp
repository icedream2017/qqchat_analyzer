#include "textprocessor.h"


TextProcessor::TextProcessor()
{
}

TextProcessor::TextProcessor(QString file)
{
    this->filename = file;
    this->cid = 0;
    this->flag = false;
}

void TextProcessor::run()
{
    this->preprocess();
}

void TextProcessor::preprocess()
{
    QFile file(filename);
    QString line;
    QTime ti;
    int prog;
    bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug(isOpen?"opened":"not opened");
    if(!isOpen) {
        file.close();
        emit process_fin();
        this->terminate();
        return;
    }
    this->fileLength = file.size();
    qDebug() << "File Length:" << this->fileLength;
    QTextStream in(&file);
    in.setCodec("Unicode");
    this->initTable();
    mydb->db.transaction();
    ti.start();
    while(!in.atEnd()) {
        line = in.readLine();
//        prog = int(in.pos()/float(this->fileLength)*100);
        qDebug() << "pos:" << in.pos();
//        emit filePos(prog);
//        qDebug(line);
        disposeInfo(line);
//        this->cache.append(line+'\n');
    }
    qDebug() << "read finished";
    file.close();
    mydb->db.commit();
    qDebug() << "time elapsed:" << ti.elapsed();
    emit process_fin();
    this->terminate();
}

int TextProcessor::getFileLength()
{
    return this->fileLength;
}

QString TextProcessor::getContent()
{
    return this->cache;
}

void TextProcessor::disposeDateTime()
{
    if(this->filename.isEmpty() | this->cache.isEmpty())
        return;
}

void TextProcessor::disposeInfo(QString str)
{
    static QRegExp dt("^\\d{4}-\\d{2}-\\d{2}");
    QSqlQuery query;
    QString sql;

//    qDebug() << str;
//    qDebug() << str.contains(dt);
    if(str.contains(dt)) {
        this->message.clear();
        this->header = str.split(" ");
//        qDebug() << header;
        this->date = header[0];
        this->time = header[1].at(1)==':'?header[1].prepend('0'):header[1];
        this->username = getQQNum(str);
    } else if(!str.contains(dt) && flag==false) {
        this->message += str;
        flag=true;
    } else if(str=="" && flag==true) {
        sql = "insert into 'chatmsg' values (";
        sql+=QString::number(this->cid)+",'"+this->date+"','"+this->time+"','"+this->username+"','"+this->message+"') ";
        query.exec(sql);
        this->cid++;
        flag=false;
    }

}

void TextProcessor::setDB(Database *db)
{
    this->mydb = db;
}

void TextProcessor::initTable()
{
    QString sql1 = "DROP TABLE IF EXISTS 'chatmsg' ";
    QString sql2 = "CREATE TABLE 'chatmsg' ('c_id' int not null, 'c_date' date not null, 'c_time' time not null, 'c_name' varchar(20) not null, 'c_msg' varchar(1000) ) ";
    QSqlQuery query;
    qDebug()<<"drop table:"<<query.exec(sql1);
    qDebug()<<"init table:"<<query.exec(sql2);
}

QString TextProcessor::getQQNum(QString str)
{
    static QRegExp re_qq("\\(\\d{5,11}\\)");
    static QRegExp re_em("<[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)+>");
    if(str.contains(re_qq)) {
        return str.mid(str.lastIndexOf(re_qq)).remove(QRegExp("[\\(\\)]"));
    } else if(str.contains(re_em)) {
        return str.mid(str.lastIndexOf(re_em)).remove(QRegExp("[<>]"));
    } else {
        return str.split(" ").at(2);
    }
}
