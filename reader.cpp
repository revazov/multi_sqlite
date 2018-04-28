#include "reader.h"
extern thread_local QSqlDatabase baseCon;

Reader::Reader(QObject *parent) : QObject(parent)
{

}

void Reader::start()
{
    qDebug() << __PRETTY_FUNCTION__ << "reader" << thread();
    baseCon = QSqlDatabase::addDatabase("QSQLITE", QString("reader%1").arg(QString::number((long long)QThread::currentThread(), 16)));

    baseCon.setDatabaseName("base.db");
    if (!baseCon.open()) {
        return;
    }
    forever {
        QSqlQuery query(baseCon);
        if(!query.exec("select count(*) from test_table;")) {
            //throwing just to terminate program
            throw(std::logic_error(QString(__PRETTY_FUNCTION__ + query.lastError().text()).toStdString()));
            break;
        }
        if(!query.first()) {
            //throwing just to terminate program
            throw(std::logic_error(QString(__PRETTY_FUNCTION__ + query.lastError().text()).toStdString()));
            break;
        }
//        thread()->msleep(100);
    }
}
